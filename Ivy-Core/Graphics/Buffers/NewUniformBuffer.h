#pragma once

#include "../Shaders/ShaderProgram.h"

// TODO: Really sloppy implementation... 
// Do not keep this as a global.
// On the plus side this means we only keep one instance of our matrices.
static struct MVP {
    glm::mat4 m_ModelMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
} m_MVP;

namespace Ivy {
namespace Graphics {

class NewUniformBuffer {
public:
    NewUniformBuffer(ShaderProgram* program) : m_Program(program) {}
    void Bind(void);
    void Create(void);
    void SetModelMatrix(glm::mat4 model);
    void SetViewMatrix(glm::mat4 view);
    void SetProjectionMatrix(glm::mat4 projection);
    void Destroy(void);
    void Unbind(void);

    private:

        ShaderProgram* m_Program;
        GLint m_UniformBufferLocation;
        GLuint m_UniformBufferID;
};
}
}