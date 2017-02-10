#pragma once

#include <d3d11shader.h>

#include "D3DRenderer.h"

namespace Ivy {
    namespace Graphics {
        class D3DShaderProgram {
            ComPtr<ID3D11VertexShader> m_pVertexShader;
            ComPtr<ID3D11ShaderReflection> m_pShaderReflector;
        };
    }
}