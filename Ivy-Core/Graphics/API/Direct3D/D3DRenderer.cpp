#include "D3DRenderer.h"

Ivy::Graphics::D3DRenderer::D3DRenderer(NativeWindow window, NativeDisplay display, 
    RendererType type, int colorBits, int depthBits, int stencilBits,
    int numSamples, int swapInterval, bool enableMultisampling, bool enableDebug) {
    this->m_Type = type;
    this->m_NativeWindow = window;
    this->m_NativeDisplay = display;
    this->m_ColorBits = colorBits;
    this->m_DepthBits = depthBits;
    this->m_StencilBits = stencilBits;
    this->m_NumSamples = numSamples;
    this->m_SwapInterval = swapInterval;
    this->m_MultisamplingEnabled = enableMultisampling;
    this->m_DebugEnabled = enableDebug;
}

Ivy::Graphics::D3DRenderer::~D3DRenderer() {
    D3DRenderer::Destroy();
}

RendererAPI Ivy::Graphics::D3DRenderer::GetRendererAPI(void)
{
    return RendererAPI::Direct3D;
}

int Ivy::Graphics::D3DRenderer::GetVersionMajor(void) {
    return m_RendererVersionMajor;
}

int Ivy::Graphics::D3DRenderer::GetVersionMinor(void) {
    return m_RendererVersionMinor;
}

void Ivy::Graphics::D3DRenderer::AdjustViewport(int width, int height) {
}

void Ivy::Graphics::D3DRenderer::Clear(glm::vec3 color) {
    m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), &color[0]);
}

bool Ivy::Graphics::D3DRenderer::Create(void)
{
    HRESULT error;
    
    int createDeviceFlags = 0;

    // Add the debug device flag along with any other defined flags.
    if(m_DebugEnabled)
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

    std::vector<D3D_DRIVER_TYPE> driverTypes = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_REFERENCE,
        D3D_DRIVER_TYPE_WARP,
    };

    std::vector<D3D_FEATURE_LEVEL> featureLevels = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
    };

    DXGI_SWAP_CHAIN_DESC swapDesc;
    ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
    swapDesc.BufferCount = 1;
    swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapDesc.OutputWindow = m_NativeWindow;
    swapDesc.Windowed = true;
    swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapDesc.SampleDesc.Count = m_NumSamples;
    swapDesc.SampleDesc.Quality = D3D11_STANDARD_MULTISAMPLE_PATTERN;
    swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    // Iterate through the drivers.
    for (unsigned int i = 0; i < driverTypes.size(); i++) {
        error = D3D11CreateDeviceAndSwapChain(nullptr, driverTypes[i], 
            nullptr, createDeviceFlags, featureLevels.data(), featureLevels.size(), D3D11_SDK_VERSION, 
            &swapDesc, m_pSwapChain.GetAddressOf(),m_pDevice.GetAddressOf(), &m_FeatureLevel, m_pImmediateContext.GetAddressOf());
        
        if (SUCCEEDED(error)) {
            // Set the feature level.
            switch (m_FeatureLevel) {
            case D3D_FEATURE_LEVEL_11_0: m_RendererVersionMajor = 11; m_RendererVersionMinor = 0; break;
            case D3D_FEATURE_LEVEL_10_1: m_RendererVersionMajor = 10; m_RendererVersionMinor = 1; break;
            case D3D_FEATURE_LEVEL_10_0: m_RendererVersionMajor = 10; m_RendererVersionMinor = 0; break;
            case D3D_FEATURE_LEVEL_9_3: m_RendererVersionMajor = 9; m_RendererVersionMinor = 3; break;
            }
            break;
        }
    }

    if (FAILED(error))
        return false;

    if (m_DebugEnabled) {
        error = m_pDevice.As(&m_pDebug);

        // TODO: Log warning.
        if (FAILED(error))
            return false;
    }

    ComPtr<ID3D11Texture2D> l_pBackBuffer;
    m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(l_pBackBuffer.GetAddressOf()));
    error = m_pDevice->CreateRenderTargetView(l_pBackBuffer.Get(), nullptr, m_pRenderTargetView.GetAddressOf());
    if (FAILED(error))
        return false;

    m_pImmediateContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), nullptr);

    ZeroMemory(&m_Viewport, sizeof(D3D11_VIEWPORT));
    m_Viewport.MinDepth = 0.0f;
    m_Viewport.MaxDepth = 1.0f;
    m_Viewport.TopLeftX = 0;
    m_Viewport.TopLeftY = 0;

    m_pImmediateContext->RSSetViewports(1, &m_Viewport);

    return true;
}

void Ivy::Graphics::D3DRenderer::Destroy(void) {
   
}

bool Ivy::Graphics::D3DRenderer::IsInitialized(void) {
    return m_pDevice != nullptr;
}

void Ivy::Graphics::D3DRenderer::Present(void) {
    if (m_DebugEnabled)
        m_pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
    m_pSwapChain->Present(1, 0);
}
