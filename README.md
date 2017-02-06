# Ivy
Collaborative C++ Game Engine written by students from the University of Memphis. 

# Dependencies 
* ANGLE
* Assimp
* FreeImage
* FreeType
* GLM
* Miniz
* PortAudio 

# Getting Started
**Windows** 

# Ivy Shader Reference
* Vertex Shader Inputs
vec3 ivy_Position - Vertex position
vec4 ivy_Color0 - Vertex color 1
vec4 ivy_Color1 - Vertex color 2, not currently used
vec3 ivy_Normal - Vertex normal vector
vec3 ivy_Tangent - Vertex tangent vector
vec3 ivy_Bitangent - Vertex bitangent vector
vec4 ivy_BlendWeight - Vertex blend weights for animation, not currently used
vec4 ivy_BlendIndices - Vertex blend indices for animation, not currently used
vec2 ivy_TexCoord0 - Vertex texture 1, Base texture
vec2 ivy_TexCoord1 - Vertex texture 2, Normal map
vec2 ivy_TexCoord2 - Vertex texture 3, not currently used
vec2 ivy_TexCoord3 - Vertex texture 4, not currently used
vec2 ivy_TexCoord4 - Vertex texture 5, not currently used
vec2 ivy_TexCoord5 - Vertex texture 6, not currently used
vec2 ivy_TexCoord6 - Vertex texture 7, not currently used
vec2 ivy_TexCoord7 - Vertex texture 8, not currently used

* Vertex Shader Uniform Blocks
ivy_MVP - mat4 ivy_Model, mat4 ivy_View, mat4 ivy_Projection
