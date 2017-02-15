#include "NewUniformBuffer.h"

void Ivy::Graphics::NewUniformBuffer::Bind(void) {
    glBindBuffer(GL_UNIFORM_BUFFER, m_UniformBufferID);
}

void Ivy::Graphics::NewUniformBuffer::Create(void) {
    // TODO: support binding point input for other objects.
    glGenBuffers(1, &m_UniformBufferID);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_UniformBufferID);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(MVP), &m_MVP, GL_STATIC_DRAW);

    m_Program->MakeActive();
    m_UniformBufferLocation = glGetUniformBlockIndex(m_Program->GetProgramID(), "ivy_MVP"); 
    glUniformBlockBinding(m_Program->GetProgramID(), m_UniformBufferLocation, 0);
    m_Program->MakeInactive();
}

void Ivy::Graphics::NewUniformBuffer::SetModelMatrix(glm::mat4 model) {
    m_MVP.m_ModelMatrix = model;
    glBufferSubData(GL_UNIFORM_BUFFER, offsetof(MVP, m_ModelMatrix), sizeof(glm::mat4), &m_MVP.m_ModelMatrix[0]);
}

void Ivy::Graphics::NewUniformBuffer::SetViewMatrix(glm::mat4 view) {
    m_MVP.m_ViewMatrix = view;
    glBufferSubData(GL_UNIFORM_BUFFER, offsetof(MVP, m_ViewMatrix), sizeof(glm::mat4), &m_MVP.m_ViewMatrix[0]);
}

void Ivy::Graphics::NewUniformBuffer::SetProjectionMatrix(glm::mat4 projection) {
    m_MVP.m_ProjectionMatrix = projection;
    glBufferSubData(GL_UNIFORM_BUFFER, offsetof(MVP, m_ProjectionMatrix), sizeof(glm::mat4), &m_MVP.m_ProjectionMatrix[0]);
}

void Ivy::Graphics::NewUniformBuffer::Destroy(void) {
    glDeleteBuffers(1, &m_UniformBufferID);
}

void Ivy::Graphics::NewUniformBuffer::Unbind(void) {
    glBindBuffer(GL_UNIFORM_BUFFER, GL_NONE);
}
