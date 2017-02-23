#include "D3DShader.h"

Ivy::Graphics::D3DShader::D3DShader(D3DRenderer* renderer, 
    ShaderType type, std::string path) : m_pRenderer(renderer) {
    m_ShaderType = type;
    m_ShaderPath = path;
}

Ivy::Graphics::D3DShader::~D3DShader() {
    D3DShader::Release();
}

void Ivy::Graphics::D3DShader::Activate() {
    switch (m_ShaderType) {
    case ShaderType::Compute:
        m_pRenderer->GetID3D11DeviceContext()->CSSetShader(m_pComputeShader.Get(), nullptr, 0); 
        break;
    case ShaderType::Domain:
        m_pRenderer->GetID3D11DeviceContext()->DSSetShader(m_pDomainShader.Get(), nullptr, 0); 
        break;
    case ShaderType::Geometry:
        m_pRenderer->GetID3D11DeviceContext()->GSSetShader(m_pGeometryShader.Get(), nullptr, 0); 
        break;
    case ShaderType::Hull:
        m_pRenderer->GetID3D11DeviceContext()->HSSetShader(m_pHullShader.Get(), nullptr, 0); 
        break;
    case ShaderType::Pixel:
        m_pRenderer->GetID3D11DeviceContext()->PSSetShader(m_pPixelShader.Get(), nullptr, 0); 
        break;
    default:
        m_pRenderer->GetID3D11DeviceContext()->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
        m_pRenderer->GetID3D11DeviceContext()->IASetInputLayout(m_pInputLayout.Get());
        break;
    }
}

bool Ivy::Graphics::D3DShader::Create() {
    unsigned int flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR;

    ComPtr<ID3DBlob> l_pErrorBlob = nullptr;
    HRESULT hr = D3DCompileFromFile(std::wstring(m_ShaderPath.begin(), m_ShaderPath.end()).c_str(), 
        nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", GetCompilerTarget(m_ShaderType).c_str(), 
        flags, 0, m_pShaderBlob.GetAddressOf(), l_pErrorBlob.GetAddressOf());

    if (l_pErrorBlob) {
        std::cerr << l_pErrorBlob->GetBufferPointer() << std::endl;
        return false;
    }
    return true;
}

void Ivy::Graphics::D3DShader::Deactivate() {
    switch (m_ShaderType) {
    case ShaderType::Compute: m_pRenderer->GetID3D11DeviceContext()->CSSetShader(nullptr, nullptr, 0);
    case ShaderType::Domain: m_pRenderer->GetID3D11DeviceContext()->DSSetShader(nullptr, nullptr, 0);
    case ShaderType::Geometry: m_pRenderer->GetID3D11DeviceContext()->GSSetShader(nullptr, nullptr, 0);
    case ShaderType::Hull: m_pRenderer->GetID3D11DeviceContext()->GSSetShader(nullptr, nullptr, 0);
    case ShaderType::Pixel: m_pRenderer->GetID3D11DeviceContext()->PSSetShader(nullptr, nullptr, 0);
    default: m_pRenderer->GetID3D11DeviceContext()->VSSetShader(nullptr, nullptr, 0);
    }
}

std::string Ivy::Graphics::D3DShader::GetShaderPath() {
    return m_ShaderPath;
}

std::string Ivy::Graphics::D3DShader::GetShaderSource() {
    return m_ShaderSource;
}

Ivy::Graphics::ShaderType Ivy::Graphics::D3DShader::GetShaderType() {
    return m_ShaderType;
}

Ivy::Graphics::ReflectionData Ivy::Graphics::D3DShader::Reflect() {
    ReflectionData reflectData;
    
    HRESULT error = D3DReflect(m_pShaderBlob->GetBufferPointer(), m_pShaderBlob->GetBufferSize(),
        IID_ID3D11ShaderReflection, reinterpret_cast<void**>(m_pShaderReflection.GetAddressOf()));

    if (FAILED(error))
        return reflectData;

    // Get shader info
    D3D11_SHADER_DESC shaderDesc;
    m_pShaderReflection->GetDesc(&shaderDesc);

    // Read input layout description from shader info
    std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
    for (unsigned int i = 0; i < shaderDesc.InputParameters; i++)
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
        m_pShaderReflection->GetInputParameterDesc(i, &paramDesc);

        // Fill out input element desc
        D3D11_INPUT_ELEMENT_DESC elementDesc;
        elementDesc.SemanticName = paramDesc.SemanticName;
        elementDesc.SemanticIndex = paramDesc.SemanticIndex;
        elementDesc.InputSlot = 0;
        elementDesc.AlignedByteOffset = (i == 0) ? 0 : D3D11_APPEND_ALIGNED_ELEMENT;
        elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        elementDesc.InstanceDataStepRate = 0;

        // Determine DXGI format
        if (paramDesc.Mask == 1) {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (paramDesc.Mask <= 3) {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        }
        else if (paramDesc.Mask <= 7) {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        else if (paramDesc.Mask <= 15) {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        }

        // Save element desc
        inputLayoutDesc.push_back(elementDesc);
    }

    return reflectData;
}

void Ivy::Graphics::D3DShader::Release() {
       
}

bool Ivy::Graphics::D3DShader::CreateInputLayout() {
    D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}, 
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"BLENDWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"BLENDINDICES", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 2, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 3, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 4, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 5, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 6, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 7, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    ComPtr<ID3D11InputLayout> l_pInputLayout;
    m_pRenderer->GetID3D11Device()->CreateInputLayout(inputDesc, 16, nullptr, 0, l_pInputLayout.GetAddressOf());
    if (!l_pInputLayout)
        return false;

    m_pRenderer->GetID3D11DeviceContext()->IASetInputLayout(l_pInputLayout.Get());
    return true;
}

std::string Ivy::Graphics::D3DShader::GetCompilerTarget(ShaderType type) {
    switch (m_pRenderer->GetFeatureLevel()) {
    case D3D_FEATURE_LEVEL_11_0:
        switch (type) {
        case ShaderType::Compute: return "cs_5_0";
        case ShaderType::Domain: return "ds_5_0";
        case ShaderType::Geometry: return "gs_5_0";
        case ShaderType::Hull: return "hs_5_0";
        case ShaderType::Pixel: return "ps_5_0";
        default: return "vs_5_0";
        }
    }
    return "";
}
