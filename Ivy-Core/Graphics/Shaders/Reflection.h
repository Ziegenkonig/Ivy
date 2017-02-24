#pragma once

#include <vector>
#include <tuple>

namespace Ivy {
    namespace Graphics {
        typedef int VariableIndex;
        typedef int VariableArrayLength;
        enum class VariableType {
            Unknown,
            Boolean,
            Boolean2,
            Boolean3,
            Boolean4,
            Double,
            Double2,
            Double3,
            Double4,
            Double2x2,
            Double2x3,
            Double2x4,
            Double3x2,
            Double3x3,
            Double3x4,
            Double4x2,
            Double4x3,
            Double4x4,
            Float,
            Float2,
            Float3,
            Float4,
            Float2x2,
            Float2x3,
            Float2x4,
            Float3x2,
            Float3x3,
            Float3x4,
            Float4x2,
            Float4x3,
            Float4x4,
            Integer,
            Integer2,
            Integer3,
            Integer4,
            Sampler,
            Sampler2D,
            Sampler3D,
            SamplerCube,
            UnsignedInteger,
            UnsignedInteger2,
            UnsignedInteger3,
            UnsignedInteger4,
        };

        struct ReflectionData {
            unsigned int mNumAttributes;
            std::vector<std::tuple<std::string, VariableType, VariableIndex>> mAttributeLayout;
            unsigned int mNumUniformBlocks;
            std::vector<std::tuple<std::string, VariableIndex, std::vector<std::tuple<std::string, 
                VariableType, VariableIndex>>>> mUniformBlockLayout;
            unsigned int mNumUniforms;
            std::vector<std::tuple<std::string, VariableType, VariableIndex>> mUniformLayout;
        };
    }
}