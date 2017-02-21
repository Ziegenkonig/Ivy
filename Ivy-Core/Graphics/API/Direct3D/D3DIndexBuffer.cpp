#include "D3DIndexBuffer.h"

Ivy::Graphics::D3DIndexBuffer::~D3DIndexBuffer() {
    D3DIndexBuffer::Destroy();
}

void Ivy::Graphics::D3DIndexBuffer::Bind(void) {
    m_pRenderer->GetID3D11DeviceContext()->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}

void Ivy::Graphics::D3DIndexBuffer::Create(void) {
    if (m_pIndexBuffer)
        m_pIndexBuffer.Reset();

    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = static_cast<unsigned int>(sizeof(unsigned short) * m_Indices.size());
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    desc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = m_Indices.data();

    // Create index buffer.
    m_pRenderer->GetID3D11Device()->CreateBuffer(&desc, &InitData, m_pIndexBuffer.GetAddressOf());
}

void Ivy::Graphics::D3DIndexBuffer::Destroy(void) {

}


void Ivy::Graphics::D3DIndexBuffer::Draw(void) {
    m_pRenderer->GetID3D11DeviceContext()->DrawIndexed(static_cast<unsigned>(m_Indices.size()), 0, 0);
}

void Ivy::Graphics::D3DIndexBuffer::Unbind(void) {
    m_pRenderer->GetID3D11DeviceContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_R16_UINT, 0);
}

void Ivy::Graphics::D3DIndexBuffer::SetData(std::vector<unsigned short> data) {
    m_Indices = data;
}
