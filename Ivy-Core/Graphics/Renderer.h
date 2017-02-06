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

#ifndef IVY_RENDERER_H
#define IVY_RENDERER_H

#ifdef test
#include <assert.h>
#include <vector>
#include <iostream>

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif 

#include <glm/glm.hpp>

#include <export.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>

#include "../Symbols.h"

namespace Ivy {
    namespace Graphics {
        class IVY_API Renderer {
        public:
            Renderer(EGLint redBits, EGLint greenBits, EGLint blueBits, EGLint alphaBits, EGLint depthBits, EGLint stencilBits,
                EGLint swapIntervalbool, bool enableMultisampling, bool enableDebug, bool disableErrors);
            ~Renderer();

            void AdjustViewport(unsigned int width, unsigned int height);
            void Clear(glm::vec3 color);
            bool Create(EGLNativeWindowType window, EGLNativeDisplayType display);
            void Destroy(void);
            bool IsInitialized(void);
            void SetCullMode(GLenum cullMode);
            void SetFrontFace(GLenum frontFace);
            void SwapBuffers(void);

            EGLint GetRenderer(void) { return m_Renderer; }
            EGLint GetRendererType(void) { return m_RendererType; }
            EGLint GetVersionMajor(void) { return m_RendererVersionMajor; }
            EGLint GetVersionMinor(void) { return m_RendererVersionMinor; }

            EGLint GetRedBits(void) { return m_RedBits; }
            void SetRedBits(EGLint bits) { m_RedBits = bits; }
            EGLint GetGreenBits(void) { return m_GreenBits; }
            void SetGreenBits(EGLint bits) { m_GreenBits = bits; }
            EGLint GetBlueBits(void) { return m_BlueBits; }
            void SetBlueBits(EGLint bits) { m_BlueBits = bits; }
            EGLint GetAlphaBits(void) { return m_AlphaBits; }
            void SetAlphaBits(EGLint bits) { m_AlphaBits = bits; }
            EGLint GetDepthBits(void) { return m_DepthBits; }
            void SetDepthBits(EGLint bits) { m_DepthBits = bits; }
            EGLint GetStencilBits(void) { return m_StencilBits; }
            void SetStencilBits(EGLint bits) { m_StencilBits = bits; }
            EGLint GetSwapInverval(void) { return m_SwapInterval; }
            void SetSwapInterval(EGLint interval);

            EGLConfig GetEGLConfig(void) { return m_Config; }
            EGLDisplay GetEGLDisplay(void) { return m_Display; }
            EGLSurface GetEGLSurface(void) { return m_Surface; }
            EGLContext GetEGLContext(void) { return m_Context; }

        private:

            EGLint m_Renderer = EGL_PLATFORM_ANGLE_TYPE_DEFAULT_ANGLE;
            EGLint m_RendererType = EGL_DONT_CARE;
            EGLint m_RendererVersionMajor = EGL_DONT_CARE;
            EGLint m_RendererVersionMinor = EGL_DONT_CARE;
            EGLint m_RendererPresentPath = EGL_DONT_CARE;

            EGLint m_RedBits;
            EGLint m_GreenBits;
            EGLint m_BlueBits;
            EGLint m_AlphaBits;
            EGLint m_DepthBits;
            EGLint m_StencilBits;
            EGLint m_SwapInterval;
            bool m_MultisamplingEnabled;
            bool m_DebugEnabled;
            bool m_DisableErrors;

            EGLConfig m_Config;
            EGLDisplay m_Display;
            EGLSurface m_Surface;
            EGLContext m_Context;
        };
    }
}

#else

#include <assert.h>
#include <vector>
#include <iostream>

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

#include <glm/glm.hpp>

#include "../Symbols.h"

namespace Ivy {
    namespace Graphics {
        class Renderer {
        public:
            Renderer(GLint redBits, GLint greenBits, GLint blueBits, GLint alphaBits, GLint depthBits, GLint stencilBits,
                GLint swapIntervalbool, bool enableMultisampling, bool enableDebug, bool disableErrors);
            ~Renderer();

            void AdjustViewport(unsigned int width, unsigned int height);
            void Clear(glm::vec3 color);
            bool Create(NativeWindow window, NativeDisplay display);
            void Destroy(void);
            bool IsInitialized(void);
            void SetCullMode(GLenum cullMode);
            void SetDrawMode(GLenum drawMode);
            void SetFrontFace(GLenum frontFace);
            void Present(NativeDisplay display);

            GLint GetVersionMajor(void) { return m_RendererVersionMajor; }
            GLint GetVersionMinor(void) { return m_RendererVersionMinor; }

            GLint GetRedBits(void) { return m_RedBits; }
            void SetRedBits(GLint bits) { m_RedBits = bits; }
            GLint GetGreenBits(void) { return m_GreenBits; }
            void SetGreenBits(GLint bits) { m_GreenBits = bits; }
            GLint GetBlueBits(void) { return m_BlueBits; }
            void SetBlueBits(GLint bits) { m_BlueBits = bits; }
            GLint GetAlphaBits(void) { return m_AlphaBits; }
            void SetAlphaBits(GLint bits) { m_AlphaBits = bits; }
            GLint GetDepthBits(void) { return m_DepthBits; }
            void SetDepthBits(GLint bits) { m_DepthBits = bits; }
            GLint GetStencilBits(void) { return m_StencilBits; }
            void SetStencilBits(GLint bits) { m_StencilBits = bits; }
            GLint GetSwapInverval(void) { return m_SwapInterval; }
            void SetSwapInterval(GLint interval);

        private:

            NativeContext m_Context;
            GLint m_RendererVersionMajor;
            GLint m_RendererVersionMinor;

            GLint m_RedBits;
            GLint m_GreenBits;
            GLint m_BlueBits;
            GLint m_AlphaBits;
            GLint m_DepthBits;
            GLint m_StencilBits;
            GLint m_SwapInterval;
            bool m_MultisamplingEnabled;
            bool m_DebugEnabled;
            bool m_DisableErrors;
        };
    }
}
#endif

#endif // IVY_RENDERER_H