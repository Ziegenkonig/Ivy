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

#ifndef IVY_IDRAWABLEBUFFER_H   
#define IVY_IDRAWABLEBUFFER_H

#include <vector>

#include "../../Symbols.h"

namespace Ivy {
    namespace Graphics {
        template<typename T>
        struct IVY_API IDrawableBuffer {
            virtual void Bind(void) = 0;
            virtual void Create(void) = 0;
            virtual void Destroy(void) = 0;
            virtual void Draw(void) = 0;
            virtual void Unbind(void) = 0;
            virtual void SetData(std::vector<T> data) = 0;
        };
    }
}

#endif // IVY_IDRAWABLEBUFFER_H