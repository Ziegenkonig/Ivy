#ifndef IVY_RENDERERFACTORY_H
#define IVY_RENDERERFACTORY_H

#include <memory>

#include "../API/Direct3D/D3DRenderer.h"
#include "../API/OpenGL/WGLRenderer.h"

namespace Ivy {
    namespace Graphics {
        class RendererFactory {
        public:
            static bool GetRenderer(std::unique_ptr<IRenderer>* renderer, 
                NativeWindow window, NativeDisplay display, RendererType type, 
                int colorBits, int depthBits, int stencilBits, 
                int numSamples,int swapInterval, bool enableMultisampling, 
                bool enableDebug) {
#ifdef _WIN32
// Use D3D by default unless overridden.
#ifndef IVY_FORCE_OPENGL
                *renderer = std::make_unique<D3DRenderer>(window, display, type, colorBits, 
                    depthBits, stencilBits, numSamples, swapInterval, enableMultisampling, 
                    enableDebug);
#else
                *renderer = std::make_unique<WGLRenderer>(window, display, type, colorBits,
                    depthBits, stencilBits, numSamples, swapInterval, enableMultisampling,
                    enableDebug);
#endif
#elif
                 
#endif
                return renderer->get()->Create();
            }
        };
    }
}

#endif