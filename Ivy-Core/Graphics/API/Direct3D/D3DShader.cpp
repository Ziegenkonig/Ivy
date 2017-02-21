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
        m_pRenderer->GetID3D11DeviceContext()->CSSetShader(m_pComputeShader.Get(), nullptr, 0); break;
    case ShaderType::Domain:
        m_pRenderer->GetID3D11DeviceContext()->DSSetShader(m_pDomainShader.Get(), nullptr, 0); break;
    case ShaderType::Geometry:
        m_pRenderer->GetID3D11DeviceContext()->GSSetShader(m_pGeometryShader.Get(), nullptr, 0); break;
    case ShaderType::Hull:
        m_pRenderer->GetID3D11DeviceContext()->HSSetShader(m_pHullShader.Get(), nullptr, 0); break;
    case ShaderType::Pixel:
        m_pRenderer->GetID3D11DeviceContext()->PSSetShader(m_pPixelShader.Get(), nullptr, 0); break;
    default:
        m_pRenderer->GetID3D11DeviceContext()->VSSetShader(m_pVertexShader.Get(), nullptr, 0); break;
        m_pRenderer->GetID3D11DeviceContext()->IASetInputLayout(m_pInputLayout.Get());
    }
}

bool Ivy::Graphics::D3DShader::Create() {
    return false;
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

std::string Ivy::Graphics::D3DShader::GetVariableName(VariableType variableType, int index) {
    return std::string();
}

int Ivy::Graphics::D3DShader::GetVariableLocation(VariableType variableType, std::string variableName) {
    return 0;
}

void Ivy::Graphics::D3DShader::Release() {

}

ComPtr<IUnknown> Ivy::Graphics::D3DShader::GetShaderFromType(ShaderType type) {
    switch (type) {
    case ShaderType::Compute: return m_pComputeShader;
    case ShaderType::Domain: return m_pDomainShader;
    case ShaderType::Geometry: return m_pGeometryShader;
    case ShaderType::Hull: return m_pHullShader;
    case ShaderType::Pixel: return m_pPixelShader;
    default: return m_pVertexShader;
    }
}
