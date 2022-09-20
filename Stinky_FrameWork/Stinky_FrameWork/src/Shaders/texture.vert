#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in vec4 aColor;
out vec2 texCoord;
out vec4 colors;

uniform mat3 MTON;
uniform vec2 texelPos;
uniform vec2 texelSize;

void main() 
{
    gl_Position = vec4(vec2(MTON * vec3(aPos, 1.f)), 0.0, 1.0);
    //  using texelPos, texelSize, lenghten or shorten images size and change texel position
    texCoord = vec2(((textureCoord.x) / texelSize.x) + texelPos.x, ((textureCoord.y) / texelSize.y) + texelPos.y);

    colors = aColor;
}