#pragma once

#include <iostream>

#include "../../Renderer/IRenderer.h"

namespace Ivy {
    namespace Graphics {
        class EGLRenderer : public IRenderer {
        public:
            EGLRenderer(NativeWindow window, NativeDisplay display, RendererPath path,
                int colorBits, int depthBits, int stencilBits, int numSamples,
                int swapInterval, bool enableMultisampling, bool enableDebug);
            ~EGLRenderer();

            // Inherited via IRenderer
            virtual RendererAPI GetRendererAPI(void) override;
            virtual RendererPath GetRendererPath(void) override;
            virtual int GetVersionMajor(void) override;
            virtual int GetVersionMinor(void) override;
            virtual void AdjustViewport(int width, int height) override;
            virtual void Clear(glm::vec3 color) override;
            virtual bool CreateShaderProgram(std::shared_ptr<IShaderProgram>* shaderProgram) override;
            virtual bool CreateTexture(std::shared_ptr<ITexture>* texture, TextureType type) override;
            virtual bool CreateVertexBuffer(std::shared_ptr<IDrawableBuffer<Vertex>>* buffer) override;
            virtual bool CreateIndexBuffer(std::shared_ptr<IDrawableBuffer<unsigned short>>* buffer) override;
            virtual int GetBackBufferWidth(void) override;
            virtual int GetBackBufferHeight(void) override;
            virtual int GetColorBits(void) override;
            virtual int GetDepthBits(void) override;
            virtual int GetStencilBits(void) override;
            virtual bool Initialized(void) override;
            virtual void Present(void) override;
            virtual bool Startup(void) override;
            virtual void Shutdown(void) override;

        private:

            NativeContext m_NativeContext;
            NativeWindow m_NativeWindow;
            NativeDisplay m_NativeDisplay;
            int m_RendererVersionMajor;
            int m_RendererVersionMinor;

            RendererPath m_Path;
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