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
            Renderer(NativeWindow window, NativeDisplay display, GLint colorBits, GLint depthBits, GLint stencilBits, GLint numSamples,
                GLint swapInterval, bool enableMultisampling, bool enableDebug, bool compatibilityContext);
            ~Renderer();

            void AdjustViewport(unsigned int width, unsigned int height);
            void Clear(glm::vec3 color);
            bool Create(void);
            void Destroy(void);
            bool IsInitialized(void);
            void SetCullMode(GLenum cullMode);
            void SetDrawMode(GLenum drawMode);
            void SetFrontFace(GLenum frontFace);
            void Present(void);

            GLint GetVersionMajor(void) { return m_RendererVersionMajor; }
            GLint GetVersionMinor(void) { return m_RendererVersionMinor; }

            GLint GetColorBits(void) { return m_ColorBits; }
            void SetColorBits(GLint bits) { m_ColorBits = bits; }
            GLint GetDepthBits(void) { return m_DepthBits; }
            void SetDepthBits(GLint bits) { m_DepthBits = bits; }
            GLint GetStencilBits(void) { return m_StencilBits; }
            void SetStencilBits(GLint bits) { m_StencilBits = bits; }
            GLint GetSwapInverval(void) { return m_SwapInterval; }
            void SetSwapInterval(GLint interval);

        private:

            NativeWindow m_NativeWindow;
            NativeDisplay m_NativeDisplay;
            NativeContext m_NativeContext;
            GLint m_RendererVersionMajor;
            GLint m_RendererVersionMinor;

            GLint m_ColorBits;
            GLint m_DepthBits;
            GLint m_StencilBits;
            GLint m_SwapInterval;
            GLint m_NumSamples;
            bool m_MultisamplingEnabled;
            bool m_DebugEnabled;
            bool m_CompatibilityEnabled;
        };
    }
}

#endif // IVY_RENDERER_H