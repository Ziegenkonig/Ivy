#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "RendererTypes.h"
#include "../Shaders/IShader.h"
#include "../Textures/ITexture.h"
#include "../Buffers/IDrawableBuffer.h"
#include "../Buffers/Vertex.h"
#include "../API/IConstantBuffer.h"

namespace Ivy {
    namespace Graphics {
        struct IRenderer {
            virtual ~IRenderer() {}
            virtual void AdjustViewport(int width, int height) = 0;
            virtual void Clear(glm::vec3 color) = 0;
            virtual bool CreateShader(ShaderType type, std::string path, std::shared_ptr<IShader>* shader) = 0;
            virtual bool CreateTexture(TextureType type, std::shared_ptr<ITexture>* texture) = 0;
            virtual bool CreateVertexBuffer(std::shared_ptr<IDrawableBuffer<Vertex>>* buffer) = 0;
            virtual bool CreateIndexBuffer(std::shared_ptr<IDrawableBuffer<unsigned short>>* buffer) = 0;
            virtual bool CreateConstantBuffer(std::shared_ptr<IShader> shader, std::shared_ptr<IConstantBuffer>* buffer) = 0;
            virtual void DisableShaders() = 0;
            virtual void EnableShaders() = 0;
            virtual void PushShaderToPipeline(std::shared_ptr<IShader> shader) = 0;
            virtual int GetBackBufferWidth() = 0;
            virtual int GetBackBufferHeight() = 0;
            virtual int GetColorBits() = 0;
            virtual int GetDepthBits() = 0;
            virtual int GetStencilBits() = 0;
            virtual bool MultisamplingEnabled() = 0;
            virtual bool DebuggingEnabled() = 0;
            virtual RendererAPI GetRendererAPI(void) = 0;
            virtual RendererPath GetRendererPath(void) = 0;
            virtual int GetVersionMajor(void) = 0;
            virtual int GetVersionMinor(void) = 0;
            virtual bool Initialized(void) = 0;
            virtual void Present(void) = 0;
            virtual bool Startup(void) = 0;
            virtual void Shutdown(void) = 0;
        };
    }
}