#pragma once

namespace Ivy {
    namespace Graphics {
        enum class ShaderType {
            Compute,
            Domain,
            Geometry,
            Pixel,
            Hull,
            Vertex,
        };

        struct IShaderProgram {
            virtual ~IShaderProgram() {};
            virtual void Activate(void) = 0;
            virtual void Deactivate(void) = 0;
            virtual bool PushShader(ShaderType shaderType, std::string shaderName) = 0;
            virtual int GetBlockLocation(ShaderType shaderType, std::string blockName) = 0;
        };
    }
}
