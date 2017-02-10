#ifndef IVY_D3DRENDERER_H
#define IVY_D3DRENDERER_H

#include <iostream>
#include <vector>
#include <d3d11.h>
#include <wrl/client.h>

#include "../../Renderer/IRenderer.h"

using namespace Microsoft::WRL;

namespace Ivy {
    namespace Graphics {
        class D3DRenderer : public IRenderer {
        public:
            D3DRenderer(NativeWindow window, NativeDisplay display, RendererType type, 
                int colorBits, int depthBits, int stencilBits, int numSamples,
                int swapInterval, bool enableMultisampling, bool enableDebug);
            ~D3DRenderer();

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

            ComPtr<ID3D11Device> m_pDevice;
            ComPtr<ID3D11DeviceContext> m_pImmediateContext;
            ComPtr<IDXGISwapChain> m_pSwapChain;
            ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
            ComPtr<ID3D11Debug> m_pDebug;

            D3D_FEATURE_LEVEL m_FeatureLevel;
            D3D11_VIEWPORT m_Viewport;

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

#endif
