#include "GLConstantBuffer.h"

Ivy::Graphics::GLConstantBuffer::GLConstantBuffer(GLShader* shader) {
    m_Shader = shader;
}

void Ivy::Graphics::GLConstantBuffer::GetModelLocation(void) {

}

void Ivy::Graphics::GLConstantBuffer::GetViewLocation(void) {

}

void Ivy::Graphics::GLConstantBuffer::GetProjectionLocation(void) {

}

glm::mat4 Ivy::Graphics::GLConstantBuffer::GetModelMatrix(void) {
    return m_ModelMatrix;
}

glm::mat4 Ivy::Graphics::GLConstantBuffer::GetViewMatrix(void) {
    return m_ViewMatrix;
}

glm::mat4 Ivy::Graphics::GLConstantBuffer::GetProjectionMatrix(void) {
    return m_ProjectionMatrix;
}

void Ivy::Graphics::GLConstantBuffer::SetModelMatrix(glm::mat4 matrix) {

}

void Ivy::Graphics::GLConstantBuffer::SetViewMatrix(glm::mat4 matrix) {

}

void Ivy::Graphics::GLConstantBuffer::SetProjectionMatrix(glm::mat4 matrix) {

}
