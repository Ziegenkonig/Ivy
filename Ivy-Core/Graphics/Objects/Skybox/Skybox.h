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

#ifndef IVY_SKYBOX_H
#define IVY_SKYBOX_H

#include "../IObject.h"

namespace Ivy {
    namespace Graphics {
        class IVY_API Skybox : public IObject {
            glm::vec3 GetPosition(void) override;
            glm::vec3 GetOrientation(void) override;
            glm::vec3 GetScale(void) override;
            float GetRotation(void) override;
            
            void SetPosition(glm::vec3 position) override;
            void SetOrientation(glm::vec3 orientation) override;
            void SetScale(glm::vec3 scale) override;
            void SetRotation(float rotation) override;
        };
    }
}

#endif // IVY_SKYBOX_H
