#include "D3DRenderer.h"
#include "D3DShader.h"
#include "D3DIndexBuffer.h"
#include "D3DVertexBuffer.h"

Ivy::Graphics::D3DRenderer::D3DRenderer(NativeWindow window, NativeDisplay display, 
    RendererPath path, int colorBits, int depthBits, int stencilBits,
    int numSamples, int swapInterval, bool enableMultisampling, bool enableDebug) {
    this->m_Path = path;
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
    D3DRenderer::Shutdown();
}

void Ivy::Graphics::D3DRenderer::AdjustViewport(int width, int height) {
}

void Ivy::Graphics::D3DRenderer::Clear(glm::vec3 color) {
    m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), &color[0]);
}

bool Ivy::Graphics::D3DRenderer::CreateShader(ShaderType type, std::string path, std::shared_ptr<IShader>* shader) {
    return (*shader = std::make_shared<D3DShader>(this, type, path)) != nullptr;
}

bool Ivy::Graphics::D3DRenderer::CreateTexture(TextureType type, std::shared_ptr<ITexture>* texture) {
    return false;
}

bool Ivy::Graphics::D3DRenderer::CreateVertexBuffer(std::shared_ptr<IDrawableBuffer<Vertex>>* buffer) {
    return (*buffer = std::make_shared<D3DVertexBuffer>(this)) != nullptr;
}

bool Ivy::Graphics::D3DRenderer::CreateIndexBuffer(std::shared_ptr<IDrawableBuffer<unsigned short>>* buffer) {
    return (*buffer = std::make_shared<D3DIndexBuffer>(this)) != nullptr;
}

bool Ivy::Graphics::D3DRenderer::CreateConstantBuffer(std::shared_ptr<IShader> shaderProgram, std::shared_ptr<IConstantBuffer>* buffer) {
    return false;
}

void Ivy::Graphics::D3DRenderer::DisableShaders()
{
}

void Ivy::Graphics::D3DRenderer::EnableShaders()
{
}

void Ivy::Graphics::D3DRenderer::PushShaderToPipeline(std::shared_ptr<IShader> shader) {

}


int Ivy::Graphics::D3DRenderer::GetBackBufferWidth()
{
    return m_BackBufferWidth;
}

int Ivy::Graphics::D3DRenderer::GetBackBufferHeight()
{
    return m_BackBufferHeight;
}

int Ivy::Graphics::D3DRenderer::GetColorBits()
{
    return m_ColorBits;
}

int Ivy::Graphics::D3DRenderer::GetDepthBits()
{
    return m_DepthBits;
}

int Ivy::Graphics::D3DRenderer::GetStencilBits()
{
    return m_StencilBits;
}

bool Ivy::Graphics::D3DRenderer::MultisamplingEnabled() {
    return m_MultisamplingEnabled;
}

bool Ivy::Graphics::D3DRenderer::DebuggingEnabled() {
    return m_DebugEnabled;
}

RendererAPI Ivy::Graphics::D3DRenderer::GetRendererAPI(void)
{
    return RendererAPI::Direct3D;
}

RendererPath Ivy::Graphics::D3DRenderer::GetRendererPath(void) {
    return m_Path;
}

int Ivy::Graphics::D3DRenderer::GetVersionMajor(void) {
    return m_RendererVersionMajor;
}

int Ivy::Graphics::D3DRenderer::GetVersionMinor(void) {
    return m_RendererVersionMinor;
}

bool Ivy::Graphics::D3DRenderer::Initialized(void) {
    return m_pDevice != nullptr;
}

void Ivy::Graphics::D3DRenderer::Present(void) {
    m_pSwapChain->Present(1, 0);
}

bool Ivy::Graphics::D3DRenderer::Startup(void) {
    HRESULT error;

    int createDeviceFlags = 0;

    if (m_DebugEnabled)
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
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
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
            &swapDesc, m_pSwapChain.GetAddressOf(), m_pDevice.GetAddressOf(), &m_FeatureLevel,
            m_pDeviceContext.GetAddressOf());

        if (SUCCEEDED(error)) {
            // Set the feature level.
            switch (m_FeatureLevel) {
            case D3D_FEATURE_LEVEL_11_0: m_RendererVersionMajor = 11; m_RendererVersionMinor = 0; break;
            case D3D_FEATURE_LEVEL_10_1: m_RendererVersionMajor = 10; m_RendererVersionMinor = 1; break;
            case D3D_FEATURE_LEVEL_10_0: m_RendererVersionMajor = 10; m_RendererVersionMinor = 0; break;
            case D3D_FEATURE_LEVEL_9_3: m_RendererVersionMajor = 9; m_RendererVersionMinor = 3; break;
            case D3D_FEATURE_LEVEL_9_2: m_RendererVersionMajor = 9; m_RendererVersionMinor = 2; break;
            case D3D_FEATURE_LEVEL_9_1: m_RendererVersionMajor = 9; m_RendererVersionMinor = 1; break;
            }
            break;
        }
    }

    if (FAILED(error))
        return false;

    if (m_DebugEnabled) {
        error = m_pDevice.As(&m_pDebug);
        if (FAILED(error))
            return false;

        m_pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
    }

    ComPtr<ID3D11Texture2D> l_pBackBuffer;
    m_pSwapChain->GetBuffer(0, IID_ID3D11Texture2D, reinterpret_cast<void**>(l_pBackBuffer.GetAddressOf()));
    error = m_pDevice->CreateRenderTargetView(l_pBackBuffer.Get(), nullptr, m_pRenderTargetView.GetAddressOf());
    if (FAILED(error))
        return false;

    m_pDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), nullptr);

    ZeroMemory(&m_Viewport, sizeof(D3D11_VIEWPORT));
    m_Viewport.MinDepth = 0.0f;
    m_Viewport.MaxDepth = 1.0f;
    m_Viewport.TopLeftX = 0;
    m_Viewport.TopLeftY = 0;

    m_pDeviceContext->RSSetViewports(1, &m_Viewport);

    std::cout << "D3DRenderer::Startup | SUCCESS" << std::endl;
    return true;
}

void Ivy::Graphics::D3DRenderer::Shutdown(void) {
    std::cout << "D3DRenderer::Shutdown | SUCCESS" << std::endl;
}

ComPtr<ID3D11Device>& Ivy::Graphics::D3DRenderer::GetID3D11Device() {
    return m_pDevice;
}

ComPtr<ID3D11DeviceContext>& Ivy::Graphics::D3DRenderer::GetID3D11DeviceContext() {
    return m_pDeviceContext;
}

ComPtr<IDXGISwapChain>& Ivy::Graphics::D3DRenderer::GetIDXGISwapChain() {
    return m_pSwapChain;
}

ComPtr<ID3D11RenderTargetView>& Ivy::Graphics::D3DRenderer::GetID3D11RenderTargetView() {
    return m_pRenderTargetView;
}

D3D_FEATURE_LEVEL Ivy::Graphics::D3DRenderer::GetFeatureLevel() {
    return m_FeatureLevel;
}
