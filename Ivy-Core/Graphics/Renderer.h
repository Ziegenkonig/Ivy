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

#endif // IVY_RENDERER_H