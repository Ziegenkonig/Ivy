# Ivy
Collaborative C++ Game Engine written by students from the University of Memphis. 

# Dependencies 
* Assimp
* FreeImage
* FreeType
* GLM
* Miniz
* PortAudio 

# Getting Started
**Windows** 

# Ivy Shader Reference
##Vertex Shader Inputs
| Semantic | Type | Use |
| --- | :---: | --- |
| ivy_Position | vec3 | Position |
| ivy_Color0 | vec4 | Color 1 |
| ivy_Color1 | vec4 | Color 2 |
| ivy_Normal | vec3 | Normal vector |
| ivy_Tangent | vec3 | Tangent vector |
| ivy_Bitangent | vec3 | Bitangent vector |
| ivy_BlendWeight | vec4 | Blend weights for animation |
| ivy_BlendIndices | vec4 | Blend indices for animation |
| ivy_TexCoord0 | vec2 | Texture 1, Diffuse map |
| ivy_TexCoord1 | vec2 | Texture 2, Normal map |
| ivy_TexCoord2 | vec2 | Texture 3, N/A |
| ivy_TexCoord3 | vec2 | Texture 4, N/A |
| ivy_TexCoord4 | vec2 | Texture 5, N/A |
| ivy_TexCoord5 | vec2 | Texture 6, N/A |
| ivy_TexCoord6 | vec2 | Texture 7, N/A |
| ivy_TexCoord7 | vec2 | Texture 8, N/A |

##Vertex Shader Uniform Blocks
###ivy_MVP - 3D Transformations
| Semantic | Type | Use |
| ---| :---: | --- |
| ivy_Model | mat4 | Model matrix |
| ivy_View | mat4 | View matrix |
| ivy_Projection | mat4 | Projection matrix |
