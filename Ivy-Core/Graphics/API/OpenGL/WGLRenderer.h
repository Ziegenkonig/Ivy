#pragma once

#include <iostream>

#include "../../Renderer/IRenderer.h"

namespace Ivy {
    namespace Graphics {
        class WGLRenderer : public IRenderer {
        public:
            WGLRenderer(NativeWindow window, NativeDisplay display, RendererPath path, 
                int colorBits, int depthBits, int stencilBits, int numSamples,
                int swapInterval, bool enableMultisampling, bool enableDebug);
            ~WGLRenderer();

            // Inherited via IRenderer
            virtual RendererAPI GetRendererAPI(void) override;
            virtual RendererPath GetRendererPath(void) override;
            virtual int GetVersionMajor(void) override;
            virtual int GetVersionMinor(void) override;
            virtual void AdjustViewport(int width, int height) override;
            virtual void Clear(glm::vec3 color) override;
            virtual bool CreateShader(ShaderType type, std::string path, std::shared_ptr<IShader>* shader) override;
            virtual bool CreateTexture(TextureType type, std::shared_ptr<ITexture>* texture) override;
            virtual bool CreateVertexBuffer(std::shared_ptr<IDrawableBuffer<Vertex>>* buffer) override;
            virtual bool CreateIndexBuffer(std::shared_ptr<IDrawableBuffer<unsigned short>>* buffer) override;
            virtual bool CreateConstantBuffer(std::shared_ptr<IShader> shader, std::shared_ptr<IConstantBuffer>* buffer) override;
            virtual int GetBackBufferWidth(void) override;
            virtual int GetBackBufferHeight(void) override;
            virtual int GetColorBits(void) override;
            virtual int GetDepthBits(void) override;
            virtual int GetStencilBits(void) override;
            virtual bool MultisamplingEnabled() override;
            virtual bool DebuggingEnabled() override;
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