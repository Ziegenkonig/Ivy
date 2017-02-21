#include "WGLRenderer.h"
#include "GLVertexBuffer.h"
#include "GLIndexBuffer.h"
#include "GLConstantBuffer.h"
#include "GLShader.h"

Ivy::Graphics::WGLRenderer::WGLRenderer(NativeWindow window, NativeDisplay display,
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

Ivy::Graphics::WGLRenderer::~WGLRenderer() {
    WGLRenderer::Startup();
}

void Ivy::Graphics::WGLRenderer::AdjustViewport(int width, int height) {
    glViewport(0, 0, width, height);
}

void Ivy::Graphics::WGLRenderer::Clear(glm::vec3 color) {
    // Clear each buffer and set the back buffer to a specific color.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(color.r, color.g, color.b, 1.0f);
}

bool Ivy::Graphics::WGLRenderer::CreateShader(ShaderType type, std::string path, std::shared_ptr<IShader>* shader) {
    return (*shader = std::make_shared<GLShader>(type, path)) != nullptr;
}

bool Ivy::Graphics::WGLRenderer::CreateTexture(TextureType type, std::shared_ptr<ITexture>* texture) {
    return false;
}

bool Ivy::Graphics::WGLRenderer::CreateVertexBuffer(std::shared_ptr<IDrawableBuffer<Vertex>>* buffer) {
    return (*buffer = std::make_shared<GLVertexBuffer>()) != nullptr;
}

bool Ivy::Graphics::WGLRenderer::CreateIndexBuffer(std::shared_ptr<IDrawableBuffer<unsigned short>>* buffer) {
    return (*buffer = std::make_shared<GLIndexBuffer>()) != nullptr;
}

bool Ivy::Graphics::WGLRenderer::CreateConstantBuffer(std::shared_ptr<IShader> shader, std::shared_ptr<IConstantBuffer>* buffer) {
    return (*buffer = std::make_shared<GLConstantBuffer>(static_cast<GLShader*>(shader.get()))) != nullptr;
}

int Ivy::Graphics::WGLRenderer::GetBackBufferWidth()
{
    return 0;
}

int Ivy::Graphics::WGLRenderer::GetBackBufferHeight()
{
    return 0;
}

int Ivy::Graphics::WGLRenderer::GetColorBits()
{
    return m_ColorBits;
}

int Ivy::Graphics::WGLRenderer::GetDepthBits()
{
    return m_DepthBits;
}

int Ivy::Graphics::WGLRenderer::GetStencilBits()
{
    return m_StencilBits;
}

RendererAPI Ivy::Graphics::WGLRenderer::GetRendererAPI(void) {
    return RendererAPI::OpenGL;
}

RendererPath Ivy::Graphics::WGLRenderer::GetRendererPath(void)
{
    return RendererPath();
}

int Ivy::Graphics::WGLRenderer::GetVersionMajor(void) {
    return m_RendererVersionMajor;
}

int Ivy::Graphics::WGLRenderer::GetVersionMinor(void) {
    return m_RendererVersionMinor;
}

bool Ivy::Graphics::WGLRenderer::Initialized(void) {
    return m_NativeContext != nullptr;
}

void Ivy::Graphics::WGLRenderer::Present(void) {
    SwapBuffers(m_NativeDisplay);
}

bool Ivy::Graphics::WGLRenderer::Startup(void) {
    // Dummy Window for legacy OpenGL context.
    HWND dummyWND = CreateWindowA("STATIC", "", WS_DISABLED, 0, 0, 0, 0, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
    HDC dummyDC = GetDC(dummyWND);

    // Describes the pixel format for our OpenGL context.
    PIXELFORMATDESCRIPTOR dummyPixelFormatDescriptor = {
        sizeof dummyPixelFormatDescriptor, 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA, static_cast<BYTE>(m_ColorBits),
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        static_cast<BYTE>(m_DepthBits), static_cast<BYTE>(m_StencilBits), 0, PFD_MAIN_PLANE, 0, 0, 0, 0
    };

    int dummyPixelFormat = ChoosePixelFormat(dummyDC, &dummyPixelFormatDescriptor);

    if (!SetPixelFormat(dummyDC, dummyPixelFormat, &dummyPixelFormatDescriptor))
        return false;

    // Create dummy context
    HGLRC dummyGLRC = wglCreateContext(dummyDC);
    wglMakeCurrent(dummyDC, dummyGLRC);

    // Initialze OpenGL functions for dummy context.
    GLenum error = glewInit();
    if (error != GLEW_NO_ERROR)
        return false;

    // Highest supported OpenGL version.
    // Used to generate a context.
    glGetIntegerv(GL_MAJOR_VERSION, &m_RendererVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &m_RendererVersionMinor);

    // Anything below 3.2 is unsupported.
    if (m_RendererVersionMajor < 3 && m_RendererVersionMinor < 2)
        return false;

    // Check for wgl extension support.
    if (!wglewIsSupported("WGL_ARB_pixel_format") && !wglewIsSupported("WGL_ARB_create_context")
        && !wglewIsSupported("WGL_ARB_multisample") && !wglewIsSupported("WGL_EXT_swap_control"))
        return false;

    if (!glewIsSupported("GL_ARB_separate_shader_objects") && !glewIsSupported("GL_ARB_get_program_binary") 
        && !glewIsSupported("GL_ARB_program_interface_query"))
        return false;

    // Choose final pixel format
    const int pixelAttribs[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, m_ColorBits,
        WGL_DEPTH_BITS_ARB, m_DepthBits,
        WGL_STENCIL_BITS_ARB, m_StencilBits,
        WGL_SAMPLE_BUFFERS_ARB, m_MultisamplingEnabled ? GL_TRUE : GL_FALSE,
        WGL_SAMPLES_ARB, m_NumSamples > 1 && m_MultisamplingEnabled ? m_NumSamples : GL_NONE,
        GL_NONE,
    };

    int pixelFormat;
    unsigned int formatCount;
    wglChoosePixelFormatARB(m_NativeDisplay, pixelAttribs, nullptr, 1, &pixelFormat, &formatCount);
    if (!formatCount)
        return false;

    if (!SetPixelFormat(m_NativeDisplay, pixelFormat, &dummyPixelFormatDescriptor))
        return false;

    int contextAttribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, m_RendererVersionMajor,
        WGL_CONTEXT_MINOR_VERSION_ARB, m_RendererVersionMinor,
        WGL_CONTEXT_FLAGS_ARB, m_DebugEnabled ? WGL_CONTEXT_DEBUG_BIT_ARB : GL_NONE,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        GL_NONE,
    };

    // Create the actual OpenGL context		
    m_NativeContext = wglCreateContextAttribsARB(m_NativeDisplay, nullptr, contextAttribs);

    // Failed to be created.
    if (!m_NativeContext)
        return false;

    // Unbind dummy context and delete.
    wglMakeCurrent(dummyDC, nullptr);
    wglDeleteContext(dummyGLRC);
    ReleaseDC(dummyWND, dummyDC);

    // Bind main context and destroy dummy window.
    wglMakeCurrent(m_NativeDisplay, m_NativeContext);
    DestroyWindow(dummyWND);

    // Initialize OpenGL pointers for new context.
    // While the methods would still "seemingly"
    // function correctly, this could lead to 
    // unusual and unintended behavior.
    error = glewInit();
    if (error != GLEW_NO_ERROR)
        return false;

    wglSwapIntervalEXT(m_SwapInterval);

    // Enable default depth and stencil testing.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);

    std::cout << "[Renderer Information]" << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl;
    GLint viewportInfo[4];
    glGetIntegerv(GL_VIEWPORT, viewportInfo);
    std::cout << "Resolution: " << viewportInfo[2] << "x" << viewportInfo[3] << std::endl;

    std::cout << "WGLRenderer::Startup | SUCCESS" << std::endl;
    return true;
}

void Ivy::Graphics::WGLRenderer::Shutdown(void) {
    wglMakeCurrent(m_NativeDisplay, nullptr);
    wglDeleteContext(m_NativeContext);
    ReleaseDC(m_NativeWindow, m_NativeDisplay);
    std::cout << "WGLRenderer::Shutdown | SUCCESS" << std::endl;
}