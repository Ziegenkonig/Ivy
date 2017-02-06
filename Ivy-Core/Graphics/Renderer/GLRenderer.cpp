#include "GLRenderer.h"

Ivy::Graphics::GLRenderer::GLRenderer(GLint redBits, GLint greenBits, GLint blueBits, GLint alphaBits, GLint depthBits, 
    GLint stencilBits, GLint swapIntervalbool, bool enableMultisampling, bool enableDebug, bool disableErrors) {     
    this->m_RedBits = redBits;       
    this->m_GreenBits = greenBits;        
    this->m_BlueBits = blueBits;        
    this->m_AlphaBits = alphaBits;        
    this->m_DepthBits = depthBits;      
    this->m_StencilBits = stencilBits;       
    this->m_MultisamplingEnabled = enableMultisampling;        
    this->m_DebugEnabled = enableDebug;     
    this->m_DisableErrors = disableErrors;
}

bool Ivy::Graphics::GLRenderer::Create(NativeWindow window, NativeDisplay display) {
#if defined(_WIN32)
    // Dummy Window for legacy OpenGL context.
    HWND dummyWND = CreateWindowA("STATIC", "", WS_DISABLED, 0, 0, 0, 0, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
    HDC dummyDC = GetDC(dummyWND);

    // Describes the pixel format for our OpenGL context.
    PIXELFORMATDESCRIPTOR dummyPixelFormatDescriptor = {
        sizeof dummyPixelFormatDescriptor, 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA, static_cast<BYTE>(m_RedBits + m_GreenBits + m_BlueBits + m_AlphaBits), 
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
    int major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    // Anything below 3.2 is unsupported.
    if (major < 3 && minor < 2)
        return false;

    // Initialze WGL functions.
    error = wglewInit();
    if (error != GLEW_NO_ERROR)
        return false;

    if (!wglewIsSupported("WGL_ARB_pixel_format") && !wglewIsSupported("WGL_ARB_create_context")
        && !wglewIsSupported("WGL_ARB_multisample") && !wglewIsSupported("WGL_EXT_swap_control"))
        return false;

    // Choose final pixel format
    const int pixelAttribs[] =
    {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, m_RedBits + m_GreenBits + m_BlueBits + m_AlphaBits,
        WGL_DEPTH_BITS_ARB, m_DepthBits,
        WGL_STENCIL_BITS_ARB, m_StencilBits,
        WGL_SAMPLE_BUFFERS_ARB, m_MultisamplingEnabled ? GL_TRUE : GL_FALSE,
        //WGL_SAMPLES_ARB, (specification.samples > 1) ? specification.samples : 0,
        GL_NONE,
    };

    int pixelFormat;
    unsigned int formatCount;
    wglChoosePixelFormatARB(display, pixelAttribs, nullptr, 1, &pixelFormat, &formatCount);

    if (!formatCount)
        return false;

    BOOL pixelFormatStatus = SetPixelFormat(display, pixelFormat, &dummyPixelFormatDescriptor);
    if (!pixelFormatStatus)
        return false;

    int contextAttribs[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 5,
        0, GL_NONE,
    };

    // Create the actual OpenGL context		
    m_Context = wglCreateContextAttribsARB(display, nullptr, contextAttribs);

    // Failed to be created.
    if (!m_Context)
        return false;

    // Unbind dummy context and delete.
    wglMakeCurrent(display, nullptr);
    wglDeleteContext(dummyGLRC);
    ReleaseDC(dummyWND, dummyDC);

    // Bind main context and destroy dummy window.
    wglMakeCurrent(display, m_Context);
    DestroyWindow(dummyWND);

    // Initialize OpenGL pointers for new context.
    // While the methods would still "seemingly"
    // function correctly, this could lead to 
    // unusual and unintended behavior.
    error = glewInit();
    if (error != GLEW_NO_ERROR)
        return false;

    return true;
#endif
}
