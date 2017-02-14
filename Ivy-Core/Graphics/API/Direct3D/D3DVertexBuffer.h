#pragma once

#include "D3DRenderer.h"
#include "../IVertexBuffer.h"

namespace Ivy {
    namespace Graphics {
        class D3DVertexBuffer : public IVertexBuffer {
        public:
            D3DVertexBuffer(D3DRenderer* renderer) : m_pRenderer(renderer) {}
        private:
            D3DRenderer* m_pRenderer;
        };
    }
}