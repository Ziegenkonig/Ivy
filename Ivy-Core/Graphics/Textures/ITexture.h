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

#ifndef IVY_ITEXTURE_H
#define IVY_ITEXTURE_H

#include "../Renderer.h"

namespace Ivy {
    namespace Graphics {

        enum class IVY_API WrapMode {
            Repeat,
            MirroredRepeat,
            ClampToEdge,
            ClampToBorder,
            MirroredClampToEdge,
        };

        enum class IVY_API FilterMode {
            Linear,
            Nearest,
        };

        struct IVY_API ITexture {
            virtual bool Create() = 0;
            virtual void MakeActive() = 0;
            virtual void MakeInactive() = 0;

            virtual GLuint GetTextureID() = 0;
            virtual GLuint GetSamplerLocation() = 0;
            virtual GLuint GetTextureWidth() = 0;
            virtual GLuint GetTextureHeight() = 0;
            virtual GLuint GetTexturePitch() = 0;
        };
    }
}

#endif