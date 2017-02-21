#include "D3DVertexBuffer.h"

Ivy::Graphics::D3DVertexBuffer::~D3DVertexBuffer() {
    D3DVertexBuffer::Destroy();
}

void Ivy::Graphics::D3DVertexBuffer::Bind(void) {
    unsigned int stride = sizeof(Vertex);
    unsigned int offset = 0;

    m_pRenderer->GetID3D11DeviceContext()->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
    m_pRenderer->GetID3D11DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Ivy::Graphics::D3DVertexBuffer::Create(void) {
    if (m_pVertexBuffer)
        m_pVertexBuffer.Reset();

    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = static_cast<unsigned int>(sizeof(Vertex) * m_Vertices.size());
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = m_Vertices.data();

    // Create vertex buffer.
    m_pRenderer->GetID3D11Device()->CreateBuffer(&desc, &InitData, m_pVertexBuffer.GetAddressOf());
}

void Ivy::Graphics::D3DVertexBuffer::Destroy(void) {

}

void Ivy::Graphics::D3DVertexBuffer::Draw(void) {
    m_pRenderer->GetID3D11DeviceContext()->Draw(static_cast<unsigned int>(m_Vertices.size()), 0);
}

void Ivy::Graphics::D3DVertexBuffer::Unbind(void) {
	m_pRenderer->GetID3D11DeviceContext()->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
}

void Ivy::Graphics::D3DVertexBuffer::SetData(std::vector<Vertex> data) {
    m_Vertices = data;
}
