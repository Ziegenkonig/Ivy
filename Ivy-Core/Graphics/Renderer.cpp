/*
MIT License

Copyright (c) 2017 Ben Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Renderer.h"

Ivy::Graphics::Renderer::Renderer(NativeWindow nativeWindow, NativeDisplay nativeDisplay, GLint colorBits, GLint depthBits,
    GLint stencilBits, GLint numSamples, GLint swapInterval, bool enableMultisampling, bool enableDebug, bool compatibilityContext) {
    this->m_NativeWindow = nativeWindow;
    this->m_NativeDisplay = nativeDisplay;
    this->m_ColorBits = colorBits;
    this->m_DepthBits = depthBits;
    this->m_StencilBits = stencilBits;
    this->m_NumSamples = numSamples;
    this->m_SwapInterval = swapInterval;
    this->m_MultisamplingEnabled = enableMultisampling;
    this->m_DebugEnabled = enableDebug;
    this->m_CompatibilityEnabled = compatibilityContext;
}

Ivy::Graphics::Renderer::~Renderer(void) {
    Renderer::Destroy();
}

void Ivy::Graphics::Renderer::AdjustViewport(unsigned int width, unsigned int height) {
    glViewport(0, 0, width, height);
}

void Ivy::Graphics::Renderer::Clear(glm::vec3 color) {
    // Clear each buffer and set the back buffer to a specific color.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(color.r, color.g, color.b, 1.0f);
}

bool Ivy::Graphics::Renderer::Create() {
#if defined(_WIN32)
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
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    // Anything below 3.2 is unsupported.
    if (major < 4 && minor < 3)
        return false;

    // Check for wgl extension support.
    if (!wglewIsSupported("WGL_ARB_pixel_format") && !wglewIsSupported("WGL_ARB_create_context")
        && !wglewIsSupported("WGL_ARB_multisample") && !wglewIsSupported("WGL_EXT_swap_control"))
        return false;

    if (!glewIsSupported("GL_ARB_separate_shader_objects") && !glewIsSupported("GL_ARB_get_program_binary"))
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
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_FLAGS_ARB, m_DebugEnabled ? WGL_CONTEXT_DEBUG_BIT_ARB : GL_NONE,
        WGL_CONTEXT_PROFILE_MASK_ARB, m_CompatibilityEnabled ? WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB : WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
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

    return true;
#endif
}

void Ivy::Graphics::Renderer::Destroy(void) {
#ifdef _WIN32
    wglMakeCurrent(m_NativeDisplay, nullptr);
    wglDeleteContext(m_NativeContext);
    ReleaseDC(m_NativeWindow, m_NativeDisplay);
#endif
}

bool Ivy::Graphics::Renderer::Initialized(void) {
    return m_NativeContext != nullptr;
}

void Ivy::Graphics::Renderer::SetCullMode(GLenum cullMode) {
    glCullFace(cullMode);
    glEnable(GL_CULL_FACE);
}

void Ivy::Graphics::Renderer::SetDrawMode(GLenum drawMode) {
    glPolygonMode(GL_FRONT_AND_BACK, drawMode);
}

void Ivy::Graphics::Renderer::SetFrontFace(GLenum frontFace) {
    glFrontFace(frontFace);
}

void Ivy::Graphics::Renderer::Present(void) {
#ifdef _WIN32
    // Swaps the front and back buffer.
    SwapBuffers(m_NativeDisplay);
#endif
}

void Ivy::Graphics::Renderer::SetSwapInterval(GLint interval) {
#ifdef _WIN32
    wglSwapIntervalEXT(interval);
    m_SwapInterval = interval;
#endif
}
