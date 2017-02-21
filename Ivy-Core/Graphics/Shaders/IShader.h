#pragma once

#include <string>

namespace Ivy {
    namespace Graphics {
        enum class VariableType {
            Input,
            Output,
            Uniform,
            Block
        };

        enum class ShaderType {
            Compute,
            Domain,
            Geometry,
            Pixel,
            Hull,
            Vertex,
        };

        enum class InternalType {
            Integer,
            Float,
            Matrix,
            Vector,
            Sampler2D,
        };

        struct IShader {
            virtual void Activate() = 0;
            virtual bool Create() = 0;
            virtual void Deactivate() = 0;
            virtual std::string GetShaderPath() = 0;
            virtual std::string GetShaderSource() = 0;
            virtual ShaderType GetShaderType() = 0;
            virtual std::string GetVariableName(VariableType variableType, int index) = 0;
            virtual int GetVariableLocation(VariableType variableType, std::string variableName) = 0;
            virtual void Release() = 0;
        };
    }
}