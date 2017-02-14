#ifndef IVY_RENDERERTYPES_H
#define IVY_RENDERERTYPES_H

#define GLEW_STATIC
#include <GL/glew.h>
#if defined(_WIN32)
#include <GL/wglew.h>
typedef HGLRC NativeContext;
typedef HWND NativeWindow;
typedef HDC NativeDisplay;
#elif defined(__unix__)
#include <GL/glxew.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
typedef GLXContext NativeContext;
typedef Display* NativeDisplay;
typedef Window NativeWindow;
#else
#error Unsupported Platform.
#endif

enum class RendererAPI {
    Direct3D,
    OpenGL,
};

enum class RendererPath {
    Deferred,
    Forward,
};

#endif