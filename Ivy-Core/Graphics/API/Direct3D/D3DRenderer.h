#ifndef IVY_D3DRENDERER_H
#define IVY_D3DRENDERER_H

#include <iostream>
#include <vector>
#include <queue>
#include <d3d11.h>
#include <wrl/client.h>

#include "../../IDrawable.h"
#include "../../Renderer/IRenderer.h"

using namespace Microsoft::WRL;

namespace Ivy {
    namespace Graphics {
        class D3DRenderer : public IRenderer {
        public:
            D3DRenderer(NativeWindow window, NativeDisplay display, RendererPath path, 
                int colorBits, int depthBits, int stencilBits, int numSamples,
                int swapInterval, bool enableMultisampling, bool enableDebug);
            ~D3DRenderer();

            // Inherited via IRenderer
            virtual RendererAPI GetRendererAPI(void) override;
            virtual RendererPath GetRendererPath(void) override;
            virtual int GetVersionMajor(void) override;
            virtual int GetVersionMinor(void) override;
            virtual void AdjustViewport(int width, int height) override;
            virtual void Clear(glm::vec3 color) override;
            virtual bool CreateShaderProgram(std::shared_ptr<IShaderProgram>* shaderProgram) override;
            virtual bool CreateTexture(std::shared_ptr<ITexture>* texture, TextureType type) override;
            virtual int GetBackBufferWidth(void) override;
            virtual int GetBackBufferHeight(void) override;
            virtual int GetColorBits(void) override;
            virtual int GetDepthBits(void) override;
            virtual int GetStencilBits(void) override;
            virtual bool Initialized(void) override;
            virtual void Present(void) override;
            virtual bool Startup(void) override;
            virtual void Shutdown(void) override;

            ComPtr<ID3D11Device>& GetID3D11Device(void);
            ComPtr<ID3D11DeviceContext>& GetID3D11DeviceContext(void);
            ComPtr<IDXGISwapChain>& GetIDXGISwapChain(void);
            ComPtr<ID3D11RenderTargetView>& GetID3D11RenderTargetView(void);

        private:

            std::queue<IDrawable> m_DrawQueue;
            
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
