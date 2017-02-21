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

#ifndef IVY_GLCONSTANTBUFFER_H
#define IVY_GLCONSTANTBUFFER_H

#include <memory>
#include <glm/gtc/type_ptr.hpp>


#include "../../API/IConstantBuffer.h"
#include "GLShader.h"

namespace Ivy {
    namespace Graphics {
        class GLConstantBuffer : public IConstantBuffer {
        public:
            
            GLConstantBuffer(GLShader* shader);

        protected:
            
            // Inherited via IConstantBuffer
            virtual void GetModelLocation(void) override;
            virtual void GetViewLocation(void) override;
            virtual void GetProjectionLocation(void) override;
            virtual glm::mat4 GetModelMatrix(void) override;
            virtual glm::mat4 GetViewMatrix(void) override;
            virtual glm::mat4 GetProjectionMatrix(void) override;
            virtual void SetModelMatrix(glm::mat4 matrix) override;
            virtual void SetViewMatrix(glm::mat4 matrix) override;
            virtual void SetProjectionMatrix(glm::mat4 matrix) override;

        private:

            GLShader* m_Shader;

            int m_ModelLocation;
            int m_ViewLocation;
            int m_ProjectionLocation;

            glm::mat4 m_ModelMatrix;
            glm::mat4 m_ViewMatrix;
            glm::mat4 m_ProjectionMatrix;
        };
    }
}

#endif // IVY_GLCONSTANTBUFFER_H