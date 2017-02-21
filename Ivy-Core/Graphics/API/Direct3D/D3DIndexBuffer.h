#pragma once

#include "D3DRenderer.h"

namespace Ivy {
    namespace Graphics {
        class D3DIndexBuffer : public IDrawableBuffer<unsigned short> {
        public:

            D3DIndexBuffer(D3DRenderer* renderer) : m_pRenderer(renderer) {}
            ~D3DIndexBuffer();

        protected:

            // Inherited via IDrawableBuffer
            virtual void Bind(void) override;
            virtual void Create(void) override;
            virtual void Destroy(void) override;
            virtual void Draw(void) override;
            virtual void Unbind(void) override;
            virtual void SetData(std::vector<unsigned short> data) override;

        private:

            D3DRenderer* m_pRenderer;
            std::vector<unsigned short> m_Indices;

            ComPtr<ID3D11Buffer> m_pIndexBuffer;
        };
    }
}