#pragma once

#include <string>

#include "../../../IO/File.h"
#include "GLRenderer.h"
#include "../../Shaders/IShader.h"

namespace Ivy {
    namespace Graphics {
        // Extensions:
        // GL_ARB_program_interface_query
        // GL_ARB_separate_shader_objects
        class GLShader : public IShader {
        public:
       
            GLShader(ShaderType type, std::string path);
            ~GLShader();

            GLuint GetPipelineID();
            GLuint GetProgramID();

        protected:

            // Inherited via IShader
            virtual void Activate() override;
            virtual bool Create() override;
            virtual void Deactivate() override;
            virtual std::string GetShaderPath() override;
            virtual std::string GetShaderSource() override;
            virtual ShaderType GetShaderType() override;
            virtual std::string GetVariableName(VariableType variableType, int index) override;
            virtual int GetVariableLocation(VariableType variableType, std::string variableName) override;
            virtual void Release() override;

        private:
            
            GLenum GetShaderEnum(ShaderType type, bool useStage);
            GLenum GetInterfaceEnum(VariableType type);

            ShaderType m_ShaderType;
            GLuint m_PipelineID;
            GLuint m_ProgramID;
            std::string m_ShaderPath;
            std::string m_ShaderSource;
        };
    }
}
