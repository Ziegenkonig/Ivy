#pragma once

#include "D3DRenderer.h"

namespace Ivy {
    namespace Graphics {
        class D3DVertexBuffer : public IDrawableBuffer<Vertex> {
        public:
            
            D3DVertexBuffer(D3DRenderer* renderer) : m_pRenderer(renderer) {}
            ~D3DVertexBuffer();

        protected:

            // Inherited via IDrawableBuffer
            virtual void Bind(void) override;
            virtual void Create(void) override;
            virtual void Destroy(void) override;
            virtual void Draw(void) override;
            virtual void Unbind(void) override;
            virtual void SetData(std::vector<Vertex> data) override;

        private:
            
            D3DRenderer* m_pRenderer;
            std::vector<Vertex> m_Vertices;

            ComPtr<ID3D11Buffer> m_pVertexBuffer;
        };
    }
}