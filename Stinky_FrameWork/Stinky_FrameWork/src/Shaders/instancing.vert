#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
out vec4 Color;

uniform mat3 MTON;	//	translate * rotata * scale

void main()
{
	//	send gl_position
	gl_Position = vec4(vec2(MTON * vec3(aPos, 1.f)), 0.0, 1.0);
	Color = aColor;
}
