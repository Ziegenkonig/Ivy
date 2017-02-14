/*
#pragma once

#include <memory>
#include "IShaderProgram.h"
#include "../API/Direct3D/D3DShaderProgram.h"
#include "../Renderer/IRenderer.h"

namespace Ivy {
    namespace Graphics {
        class ShaderProgramFactory {
        public:
            static bool GetShaderProgram(std::shared_ptr<IShaderProgram>* shaderProgram, const std::shared_ptr<IRenderer>& renderer) {
                if (renderer->GetRendererAPI() == RendererAPI::Direct3D) {
                    *shaderProgram = std::make_shared<D3DShaderProgram>(std::dynamic_pointer_cast<D3DRenderer>(renderer));
                }

                return *shaderProgram != nullptr;
            }
        };
    }
}
*/