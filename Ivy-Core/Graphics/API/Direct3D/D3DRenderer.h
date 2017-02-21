#ifndef IVY_D3DRENDERER_H
#define IVY_D3DRENDERER_H

#include <iostream>
#include <vector>
#include <d3d11.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

#include "../../Renderer/IRenderer.h"

#define ivy__uuidof(NAME) IID_##NAME

using namespace Microsoft::WRL;

namespace Ivy {
    namespace Graphics {
        class D3DRenderer : public IRenderer {
        public:
            D3DRenderer(NativeWindow window, NativeDisplay display, RendererPath path, 
                int colorBits, int depthBits, int stencilBits, int numSamples,
                int swapInterval, bool enableMultisampling, bool enableDebug);
            ~D3DRenderer();

            ComPtr<ID3D11Device>& GetID3D11Device(void);
            ComPtr<ID3D11DeviceContext>& GetID3D11DeviceContext(void);
            ComPtr<IDXGISwapChain>& GetIDXGISwapChain(void);
            ComPtr<ID3D11RenderTargetView>& GetID3D11RenderTargetView(void);

        protected:

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
            virtual bool CreateConstantBuffer(std::shared_ptr<IShader> shaderProgram, std::shared_ptr<IConstantBuffer>* buffer) override;
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

            ComPtr<ID3D11Device> m_pDevice;
            ComPtr<ID3D11DeviceContext> m_pDeviceContext;
            ComPtr<IDXGISwapChain> m_pSwapChain;
            ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
            ComPtr<ID3D11RasterizerState> m_pRasterizerState;
            ComPtr<ID3D11Debug> m_pDebug;

            D3D_FEATURE_LEVEL m_FeatureLevel;
            D3D11_VIEWPORT m_Viewport;

            NativeWindow m_NativeWindow;
            NativeDisplay m_NativeDisplay;
            int m_RendererVersionMajor;
            int m_RendererVersionMinor;
            unsigned int m_BackBufferWidth;
            unsigned int m_BackBufferHeight;

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

#endif
