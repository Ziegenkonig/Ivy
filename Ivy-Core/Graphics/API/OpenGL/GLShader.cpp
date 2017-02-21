#include "GLShader.h"

Ivy::Graphics::GLShader::GLShader(ShaderType type, std::string path) {
    m_ShaderType = type;
    m_ShaderPath = path;
}

Ivy::Graphics::GLShader::~GLShader() {
    GLShader::Release();
}

GLuint Ivy::Graphics::GLShader::GetPipelineID() {
    return m_PipelineID;
}

GLuint Ivy::Graphics::GLShader::GetProgramID() {
    return m_ProgramID;
}

void Ivy::Graphics::GLShader::Activate() {
    glBindProgramPipeline(m_PipelineID);
    glActiveShaderProgram(m_PipelineID, m_ProgramID);
}

bool Ivy::Graphics::GLShader::Create() {
    // Read the shader and check to see if it is empty.
    // Empty signifies the file could not be found or there was no data.
    IO::File file;
    m_ShaderSource = file.Read(m_ShaderPath);
    if (m_ShaderSource.empty())
        return false;

    // Convert the std::string into an OpenGL friendly format.
    const GLchar* shaderData = m_ShaderSource.c_str();
    GLenum shader = GetShaderEnum(m_ShaderType, false);
    m_ProgramID = glCreateShaderProgramv(shader, 1, &shaderData);
    
    GLint stageStatus;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &stageStatus);
    if (stageStatus == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength > 1) {
            std::vector<GLchar>infoLog(infoLogLength);
            glGetProgramInfoLog(m_ProgramID, static_cast<GLsizei>(infoLog.size()), nullptr, &infoLog[0]);
            std::cerr << "ProgramID " << m_ProgramID << " failed to link with error: " << &infoLog[0] << std::endl;
        }
        else 
            std::cerr << "ProgramID " << m_ProgramID << " failed to link...\n";
        
        return false;
    }

    glGenProgramPipelines(1, &m_PipelineID);
    glUseProgramStages(m_PipelineID, GetShaderEnum(m_ShaderType, true), m_ProgramID);
    return true;
}

void Ivy::Graphics::GLShader::Deactivate() {
    glBindProgramPipeline(GL_NONE);
}

std::string Ivy::Graphics::GLShader::GetShaderPath() {
    return m_ShaderPath;
}

std::string Ivy::Graphics::GLShader::GetShaderSource() {
    return m_ShaderSource;
}

Ivy::Graphics::ShaderType Ivy::Graphics::GLShader::GetShaderType() {
    return m_ShaderType;
}

std::string Ivy::Graphics::GLShader::GetVariableName(VariableType variableType, int index) {
    GLint maxNameLength;
    glGetProgramInterfaceiv(m_ProgramID, GetInterfaceEnum(variableType), GL_MAX_NAME_LENGTH, &maxNameLength);
    std::vector<char> buffer(maxNameLength);
    glGetProgramResourceName(m_ProgramID, GetInterfaceEnum(variableType), index, maxNameLength, nullptr, buffer.data());
    return std::string(buffer.data());
}

int Ivy::Graphics::GLShader::GetVariableLocation(VariableType type, std::string name) {
    return glGetProgramResourceLocation(m_ProgramID, GetInterfaceEnum(type), name.c_str());
}

void Ivy::Graphics::GLShader::Release() {
    glDeleteProgram(m_ProgramID);
    glDeleteProgramPipelines(1, &m_PipelineID);
}

GLenum Ivy::Graphics::GLShader::GetShaderEnum(ShaderType type, bool useStage) {
    switch (type) {
    case ShaderType::Compute: return useStage ? GL_COMPUTE_SHADER_BIT : GL_COMPUTE_SHADER;
    case ShaderType::Domain: return  useStage ? GL_TESS_EVALUATION_SHADER_BIT : GL_TESS_EVALUATION_SHADER;
    case ShaderType::Pixel: return useStage ? GL_FRAGMENT_SHADER_BIT : GL_FRAGMENT_SHADER;
    case ShaderType::Geometry: return  useStage ? GL_GEOMETRY_SHADER_BIT : GL_GEOMETRY_SHADER;
    case ShaderType::Hull: return useStage ? GL_TESS_CONTROL_SHADER_BIT : GL_TESS_CONTROL_SHADER;
    default: return useStage ? GL_VERTEX_SHADER_BIT : GL_VERTEX_SHADER;
    }
}

GLenum Ivy::Graphics::GLShader::GetInterfaceEnum(VariableType type) {
    switch (type) {
    case VariableType::Input:  return GL_PROGRAM_INPUT;
    case VariableType::Output: return GL_PROGRAM_OUTPUT;
    case VariableType::Block: return GL_UNIFORM_BLOCK;
    case VariableType::Uniform: return GL_UNIFORM;
    default: return GL_NONE;
    }
}
