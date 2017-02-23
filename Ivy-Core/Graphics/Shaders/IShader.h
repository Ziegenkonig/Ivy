#pragma once

#include <string>

#include "Reflection.h"

namespace Ivy {
    namespace Graphics {
        enum class VariableClassifier {
            Attribute,
            Uniform,
            UniformBlock
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
            virtual ReflectionData Reflect() = 0;
            virtual void Release() = 0;
        };
    }
}