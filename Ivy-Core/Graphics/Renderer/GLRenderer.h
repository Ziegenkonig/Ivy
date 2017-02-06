#ifndef IVY_IRENDERER_H
#define IVY_IRENDERER_H

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

#include "RendererTypes.h"

namespace Ivy {
    namespace Graphics {
        class GLRenderer {
        public:
            GLRenderer(GLint redBits, GLint greenBits, GLint blueBits, GLint alphaBits, GLint depthBits, GLint stencilBits,
                GLint swapIntervalbool, bool enableMultisampling, bool enableDebug, bool disableErrors);
            ~GLRenderer();

            void AdjustViewport(unsigned int width, unsigned int height);
            void Clear(glm::vec3 color);
            bool Create(NativeWindow window, NativeDisplay display);
            void Destroy(void);
            bool IsInitialized(void);
            void SetCullMode(GLenum cullMode);
            void SetDrawMode(GLenum drawMode);
            void SetFrontFace(GLenum frontFace);
            void SwapBuffers(void);
            
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
