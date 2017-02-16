#include "EGLRenderer.h"

Ivy::Graphics::EGLRenderer::EGLRenderer(NativeWindow window, NativeDisplay display, RendererPath path, 
    int colorBits, int depthBits, int stencilBits, int numSamples, int swapInterval, 
    bool enableMultisampling, bool enableDebug)
{
}

Ivy::Graphics::EGLRenderer::~EGLRenderer()
{
}

RendererAPI Ivy::Graphics::EGLRenderer::GetRendererAPI(void) {
    return RendererAPI();
}

RendererPath Ivy::Graphics::EGLRenderer::GetRendererPath(void) {
    return RendererPath();
}

int Ivy::Graphics::EGLRenderer::GetVersionMajor(void) {
    return 0;
}

int Ivy::Graphics::EGLRenderer::GetVersionMinor(void) {
    return 0;
}

void Ivy::Graphics::EGLRenderer::AdjustViewport(int width, int height) {
}

void Ivy::Graphics::EGLRenderer::Clear(glm::vec3 color) {
}

bool Ivy::Graphics::EGLRenderer::CreateShaderProgram(std::shared_ptr<IShaderProgram>* shaderProgram) {
    return false;
}

bool Ivy::Graphics::EGLRenderer::CreateTexture(std::shared_ptr<ITexture>* texture, TextureType type)
{
    return false;
}

bool Ivy::Graphics::EGLRenderer::CreateVertexBuffer(std::shared_ptr<IDrawableBuffer<Vertex>>* buffer) {
    return false;
}

bool Ivy::Graphics::EGLRenderer::CreateIndexBuffer(std::shared_ptr<IDrawableBuffer<unsigned short>>* buffer) {
    return false;
}

int Ivy::Graphics::EGLRenderer::GetBackBufferWidth(void)
{
    return 0;
}

int Ivy::Graphics::EGLRenderer::GetBackBufferHeight(void)
{
    return 0;
}

int Ivy::Graphics::EGLRenderer::GetColorBits(void)
{
    return 0;
}

int Ivy::Graphics::EGLRenderer::GetDepthBits(void)
{
    return 0;
}

int Ivy::Graphics::EGLRenderer::GetStencilBits(void)
{
    return 0;
}

bool Ivy::Graphics::EGLRenderer::Initialized(void)
{
    return false;
}

void Ivy::Graphics::EGLRenderer::Present(void)
{
}

bool Ivy::Graphics::EGLRenderer::Startup(void)
{
    return false;
}

void Ivy::Graphics::EGLRenderer::Shutdown(void)
{
}
