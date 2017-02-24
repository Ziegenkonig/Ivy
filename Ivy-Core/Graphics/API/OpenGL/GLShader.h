#pragma once

#include <string>

#include "../../../IO/File.h"
#include "GLRenderer.h"
#include "../../Shaders/IShader.h"
#include "../../Shaders/Reflection.h"

namespace Ivy {
    namespace Graphics {
        // Extensions:
        // GL_ARB_program_interface_query
        // GL_ARB_separate_shader_objects
        class GLShader : public IShader {
        public:
       
            GLShader(ShaderType type, std::string path);
            ~GLShader();

            void BindToPipeline(GLint pipelineID);
            GLuint GetProgramID();

        protected:

            // Inherited via IShader
            virtual void Activate() override;
            virtual bool Create() override;
            virtual void Deactivate() override;
            virtual std::string GetShaderPath() override;
            virtual std::string GetShaderSource() override;
            virtual ShaderType GetShaderType() override;
            virtual ReflectionData Reflect() override;
            virtual void Release() override;

        private:
            
            GLenum GetShaderEnum(ShaderType type, bool useStage);
            GLenum GetInterfaceEnum(VariableClassifier type);
            VariableType GLenumToVariableType(GLenum param);

            ShaderType m_ShaderType;
            GLuint m_PipelineID;
            GLuint m_ProgramID;
            std::string m_ShaderPath;
            std::string m_ShaderSource;
        };
    }
}
