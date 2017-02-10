#pragma once

#include <glm/glm.hpp>

#include "RendererTypes.h"

namespace Ivy {
    namespace Graphics {
        struct IRenderer {
            virtual ~IRenderer() {};
            virtual RendererAPI GetRendererAPI(void) = 0;
            virtual int GetVersionMajor(void) = 0;
            virtual int GetVersionMinor(void) = 0;
            virtual void AdjustViewport(int width, int height) = 0;
            virtual void Clear(glm::vec3 color) = 0;
            virtual bool Create(void) = 0;
            virtual void Destroy(void) = 0;
            virtual bool IsInitialized(void) = 0;
            virtual void Present(void) = 0;

            /*
            virtual RendererType GetRendererType(void) = 0;
            virtual int GetBackBufferWidth() = 0;
            virtual int GetBackBufferHeight() = 0;
            virtual int GetColorBits() = 0;
            virtual int GetDepthBits() = 0;
            virtual int GetStencilBits() = 0;

            */
        };
    }
}