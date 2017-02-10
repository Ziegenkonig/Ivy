#pragma once

#include <iostream>

#include "../../Renderer/IRenderer.h"

namespace Ivy {
    namespace Graphics {
        class WGLRenderer : public IRenderer {
        public:
            WGLRenderer(NativeWindow window, NativeDisplay display, RendererType type, 
                int colorBits, int depthBits, int stencilBits, int numSamples,
                int swapInterval, bool enableMultisampling, bool enableDebug);
            ~WGLRenderer();

            // Inherited via IRenderer
            virtual RendererAPI GetRendererAPI(void) override;
            virtual int GetVersionMajor(void) override;
            virtual int GetVersionMinor(void) override;
            virtual void AdjustViewport(int width, int height) override;
            virtual void Clear(glm::vec3 color) override;
            virtual bool Create(void) override;
            virtual void Destroy(void) override;
            virtual bool IsInitialized(void) override;
            virtual void Present(void) override;

        private:

            NativeContext m_NativeContext;
            NativeWindow m_NativeWindow;
            NativeDisplay m_NativeDisplay;
            int m_RendererVersionMajor;
            int m_RendererVersionMinor;

            RendererType m_Type;
            int m_ColorBits;
            int m_DepthBits;
            int m_StencilBits;
            int m_SwapInterval;
            int m_NumSamples;
            bool m_MultisamplingEnabled;
            bool m_DebugEnabled;
        };
    }
}