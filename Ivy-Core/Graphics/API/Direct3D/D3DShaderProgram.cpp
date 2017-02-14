#include "D3DShaderProgram.h"

Ivy::Graphics::D3DShaderProgram::~D3DShaderProgram() {

}

void Ivy::Graphics::D3DShaderProgram::Activate(void) {
}

void Ivy::Graphics::D3DShaderProgram::Deactivate(void) {
}

bool Ivy::Graphics::D3DShaderProgram::PushShader(ShaderType shaderType, std::string shaderName) {
    // Compile shader.
    ComPtr<ID3DBlob> l_pError;
    HRESULT error = D3DCompileFromFile(std::wstring(shaderName.begin(), shaderName.end()).c_str(), nullptr, 
        D3D_COMPILE_STANDARD_FILE_INCLUDE, "Main", GetShaderTarget(shaderType).c_str(), D3DCOMPILE_DEBUG, 0, 
        GetShaderBlob(shaderType).GetAddressOf(), l_pError.GetAddressOf());
  
    // Log shader compilation error.
    if (l_pError != nullptr)
        std::cerr << l_pError->GetBufferPointer() << std::endl;

    return !FAILED(error);
}

int Ivy::Graphics::D3DShaderProgram::GetBlockLocation(ShaderType shaderType, std::string blockName) {
    // Check for empty shader blob before attemtping to retrieve pointer.
    if (!GetShaderBlob(shaderType))
        return -1;

    ComPtr<ID3D11ShaderReflection> l_pShaderReflection;
    HRESULT error = D3DReflect(GetShaderBlob(shaderType)->GetBufferPointer(), GetShaderBlob(shaderType)->GetBufferSize(),
        IID_ID3D11ShaderReflection, reinterpret_cast<void**>(l_pShaderReflection.GetAddressOf()));
    
    // Failed to reflect shader.
    if (FAILED(error))
        return error;
    
    D3D11_SHADER_DESC shaderDesc;
    l_pShaderReflection->GetDesc(&shaderDesc);

    for (unsigned int i = 0; i < shaderDesc.ConstantBuffers; i++) {
        ID3D11ShaderReflectionConstantBuffer* constantBuffer = 
            l_pShaderReflection->GetConstantBufferByIndex(i);
        D3D11_SHADER_BUFFER_DESC constantBufferDesc;
        constantBuffer->GetDesc(&constantBufferDesc);
        if (blockName.c_str() == constantBufferDesc.Name)
            return i;
    }

    // Block name not found.
    return -1;
}

bool Ivy::Graphics::D3DShaderProgram::CreateShader(ShaderType shaderType) {
    return false;
}

ComPtr<ID3DBlob>& Ivy::Graphics::D3DShaderProgram::GetShaderBlob(ShaderType shaderType) {
    switch (shaderType) {
    case ShaderType::Compute: return m_pComputeShaderBlob;
    case ShaderType::Domain: return m_pDomainShaderBlob;
    case ShaderType::Geometry: return m_pGeometryShaderBlob;
    case ShaderType::Hull: return m_pHullShaderBlob;
    case ShaderType::Pixel: return m_pPixelShaderBlob;
    default: return m_pVertexShaderBlob;
    }
}

std::string Ivy::Graphics::D3DShaderProgram::GetShaderTarget(ShaderType shaderType) {
    switch (shaderType) {
    case ShaderType::Compute: return "cs_5_0";
    case ShaderType::Domain: return "ds_5_0";
    case ShaderType::Geometry: return "gs_5_0";
    case ShaderType::Hull: return "hs_5_0";
    case ShaderType::Pixel: return "ps_5_0";
    default: return "vs_5_0";
    }
}
