#ifndef IVY_ICONSTANTBUFFER_H
#define IVY_ICONSTANTBUFFER_H

#include <glm/glm.hpp>

namespace Ivy {
    namespace Graphics {
        struct IConstantBuffer {
            virtual void GetModelLocation(void) = 0;
            virtual void GetViewLocation(void) = 0;
            virtual void GetProjectionLocation(void) = 0;

            virtual glm::mat4 GetModelMatrix(void) = 0;
            virtual glm::mat4 GetViewMatrix(void) = 0;
            virtual glm::mat4 GetProjectionMatrix(void) = 0;

            virtual void SetModelMatrix(glm::mat4 matrix) = 0;
            virtual void SetViewMatrix(glm::mat4 matrix) = 0;
            virtual void SetProjectionMatrix(glm::mat4 matrix) = 0;
        };
    }
}

#endif