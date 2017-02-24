#include "GLShader.h"

Ivy::Graphics::GLShader::GLShader(ShaderType type, std::string path) {
    m_ShaderType = type;
    m_ShaderPath = path;
}

Ivy::Graphics::GLShader::~GLShader() {
    GLShader::Release();
}

void Ivy::Graphics::GLShader::BindToPipeline(GLint pipelineID) {
    m_PipelineID = pipelineID;
    glUseProgramStages(m_PipelineID, GetShaderEnum(m_ShaderType, true), m_ProgramID);
}

GLuint Ivy::Graphics::GLShader::GetProgramID() {
    return m_ProgramID;
}

void Ivy::Graphics::GLShader::Activate() {
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

    return true;
}

void Ivy::Graphics::GLShader::Deactivate() {
    //glBindProgramPipeline(GL_NONE);
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

Ivy::Graphics::ReflectionData Ivy::Graphics::GLShader::Reflect() {
    ReflectionData reflectData;

    // Get the number of each type of resource that is active.
    GLint activeAttributes;
    GLint activeUniforms;
    GLint activeUniformBlocks;
    glGetProgramInterfaceiv(m_ProgramID, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &activeAttributes);
    glGetProgramInterfaceiv(m_ProgramID, GL_UNIFORM, GL_ACTIVE_RESOURCES, &activeUniforms);
    glGetProgramInterfaceiv(m_ProgramID, GL_UNIFORM_BLOCK, GL_ACTIVE_RESOURCES, &activeUniformBlocks);
    reflectData.mNumAttributes = activeAttributes;
    reflectData.mNumUniforms = activeUniforms;
    reflectData.mNumUniformBlocks = activeUniformBlocks;

    for (int i = 0; i < activeAttributes; i++) {
        // GL_TYPE: returns the type of uniform this is, eg. GL_FLOAT, GL_FLOAT_VEC2.
        // GL_LOCATION: index where this attribute is located.
        // GL_NAME_LENGTH: length of the name of this uniform.
        GLenum attributeProperties[] = { GL_TYPE, GL_LOCATION, GL_NAME_LENGTH };
        GLint attributeParams[3];

        glGetProgramResourceiv(m_ProgramID, GL_PROGRAM_INPUT, i, 3, attributeProperties, 3, nullptr, attributeParams);
        std::vector<char> buffer(attributeParams[2]);
        glGetProgramResourceName(m_ProgramID, GL_PROGRAM_INPUT, i, buffer.size(), nullptr, buffer.data());
       
        reflectData.mAttributeLayout.push_back(std::tuple<std::string, VariableType, 
            VariableIndex>(buffer.data(), GLenumToVariableType(attributeParams[0]), attributeParams[1]));
    }

    for (int i = 0; i < activeUniforms; i++) {
        // GL_TYPE: returns the type of uniform this is, eg. GL_FLOAT, GL_FLOAT_VEC2.
        // GL_LOCATION: index where this uniform is located.
        // GL_NAME_LENGTH: length of the name of this uniform.
        GLenum uniformProperties[] = { GL_TYPE, GL_LOCATION, GL_NAME_LENGTH };
        GLint uniformParams[3];
        
        glGetProgramResourceiv(m_ProgramID, GL_UNIFORM, i, 3, uniformProperties, 3, nullptr, uniformParams);
        std::vector<char> buffer(uniformParams[2]);
        glGetProgramResourceName(m_ProgramID, GL_UNIFORM, i, buffer.size(), nullptr, buffer.data());
        
        reflectData.mUniformLayout.push_back(std::tuple<std::string, VariableType, 
            VariableIndex>(buffer.data(), GLenumToVariableType(uniformParams[0]), uniformParams[1]));
    }

    for (int currentUniformBlock = 0; currentUniformBlock < activeUniformBlocks; currentUniformBlock++) {
        // GL_BUFFER_BINDING: slot for the uniform block to be binded to.
        // GL_NAME_LENGTH: length of the name of this uniform.
        // GL_NUM_ACTIVE_VARIABLES: number of active uniforms within the block.
        GLenum uniformBlockProperties[] = { GL_BUFFER_BINDING, GL_NAME_LENGTH, GL_NUM_ACTIVE_VARIABLES };
        GLint uniformBlockParams[3];
        glGetProgramResourceiv(m_ProgramID, GL_UNIFORM_BLOCK, currentUniformBlock, 3, uniformBlockProperties, 3, nullptr, uniformBlockParams);
        GLint numActiveUniforms = uniformBlockParams[2];

        // GL_ACTIVE_VARIABLES: the indices of the uniform variables within the block.
        // This will fill up our activeBlockUniforms vector with an array of indices of size GL_NUM_ACTIVE_VARIABLES.
        GLenum activeBlockUniformsProp[] = { GL_ACTIVE_VARIABLES };
        std::vector<GLint> activeBlockUniforms(numActiveUniforms);
        glGetProgramResourceiv(m_ProgramID, GL_UNIFORM_BLOCK, currentUniformBlock, 1, activeBlockUniformsProp, numActiveUniforms, 
            nullptr, activeBlockUniforms.data());

        // Gets the name of the uniform block.
        std::vector<char> uniformBlockName(uniformBlockParams[1]);
        glGetProgramResourceName(m_ProgramID, GL_UNIFORM_BLOCK, currentUniformBlock, uniformBlockName.size(), nullptr, uniformBlockName.data());

        std::vector<std::tuple<std::string, VariableType, VariableIndex>> uniformBlockVariables;
        for (int currentUniform = 0; currentUniform < numActiveUniforms; currentUniform++) {
            // GL_TYPE: returns the type of uniform this is, eg. GL_FLOAT, GL_FLOAT_VEC2.
            // GL_NAME_LENGTH: length of the name of this uniform.
            GLenum variableProps[] = { GL_TYPE, GL_NAME_LENGTH };
            GLint variableParams[2];

            // Get the type and name of the uniforms.
            glGetProgramResourceiv(m_ProgramID, GL_UNIFORM, activeBlockUniforms[currentUniform], 2, variableProps, 2, nullptr, variableParams);
            std::vector<char> variableName(variableParams[1]);
            glGetProgramResourceName(m_ProgramID, GL_UNIFORM, activeBlockUniforms[currentUniform], variableName.size(), nullptr, variableName.data());
            
            uniformBlockVariables.push_back(std::tuple<std::string, VariableType, VariableIndex>(variableName.data(), 
                GLenumToVariableType(variableParams[0]), activeBlockUniforms[currentUniform]));
        }

        reflectData.mUniformBlockLayout.push_back(std::tuple<std::string, VariableIndex, 
            std::vector<std::tuple<std::string, VariableType, VariableIndex>>>(uniformBlockName.data(), uniformBlockParams[0], 
                uniformBlockVariables));
    }

    return reflectData;
}

void Ivy::Graphics::GLShader::Release() {
    glDeleteProgram(m_ProgramID);
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

GLenum Ivy::Graphics::GLShader::GetInterfaceEnum(VariableClassifier type) {
    switch (type) {
    case VariableClassifier::Attribute:  return GL_PROGRAM_INPUT;
    case VariableClassifier::UniformBlock: return GL_UNIFORM_BLOCK;
    case VariableClassifier::Uniform: return GL_UNIFORM;
    default: return GL_NONE;
    }
}

Ivy::Graphics::VariableType Ivy::Graphics::GLShader::GLenumToVariableType(GLenum param) {
    switch (param) {
    case GL_BOOL: return VariableType::Boolean;
    case GL_BOOL_VEC2: return VariableType::Boolean2;
    case GL_BOOL_VEC3: return VariableType::Boolean3;
    case GL_BOOL_VEC4: return VariableType::Boolean4;
    case GL_DOUBLE: return VariableType::Double;
    case GL_DOUBLE_VEC2: return VariableType::Double2;
    case GL_DOUBLE_VEC3: return VariableType::Double3;
    case GL_DOUBLE_VEC4: return VariableType::Double4;
    case GL_DOUBLE_MAT2: return VariableType::Double2x2;
    case GL_DOUBLE_MAT2x3: return VariableType::Double2x3;
    case GL_DOUBLE_MAT2x4: return VariableType::Double2x4;
    case GL_DOUBLE_MAT3x2: return VariableType::Double3x2;
    case GL_DOUBLE_MAT3: return VariableType::Double3x3;
    case GL_DOUBLE_MAT3x4: return VariableType::Double3x4;
    case GL_DOUBLE_MAT4x2: return VariableType::Double4x2;
    case GL_DOUBLE_MAT4x3: return VariableType::Double4x3;
    case GL_DOUBLE_MAT4: return VariableType::Double4x4;
    case GL_FLOAT: return VariableType::Float;
    case GL_FLOAT_VEC2: return VariableType::Float2;
    case GL_FLOAT_VEC3: return VariableType::Float3;
    case GL_FLOAT_VEC4: return VariableType::Float4;
    case GL_FLOAT_MAT2: return VariableType::Float2x2;
    case GL_FLOAT_MAT2x3: return VariableType::Float2x3;
    case GL_FLOAT_MAT2x4: return VariableType::Float2x4;
    case GL_FLOAT_MAT3x2: return VariableType::Float3x2;
    case GL_FLOAT_MAT3: return VariableType::Float3x3;
    case GL_FLOAT_MAT3x4: return VariableType::Float3x4;
    case GL_FLOAT_MAT4x2: return VariableType::Float4x2;
    case GL_FLOAT_MAT4x3: return VariableType::Float4x3;
    case GL_FLOAT_MAT4: return VariableType::Float4x4;
    case GL_INT: return VariableType::Integer;
    case GL_INT_VEC2: return VariableType::Integer2;
    case GL_INT_VEC3: return VariableType::Integer3;
    case GL_INT_VEC4: return VariableType::Integer4;
    case GL_SAMPLER_1D: return VariableType::Sampler;
    case GL_SAMPLER_2D: return VariableType::Sampler2D;
    case GL_SAMPLER_3D: return VariableType::Sampler3D;
    case GL_SAMPLER_CUBE: return VariableType::SamplerCube;
    case GL_UNSIGNED_INT: return VariableType::UnsignedInteger;
    case GL_UNSIGNED_INT_VEC2: return VariableType::UnsignedInteger2;
    case GL_UNSIGNED_INT_VEC3: return VariableType::UnsignedInteger3;
    case GL_UNSIGNED_INT_VEC4: return VariableType::UnsignedInteger4;
    default: return VariableType::Unknown;
    }
}
