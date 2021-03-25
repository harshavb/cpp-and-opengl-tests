// GLSL shader that  passes location data, color data, and a test garbage float

#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in float garbage_position_duplicate;

out vec3 ourColor;

void main()
{
	gl_Position = vec4(aPos, 1.0f);
	ourColor = vertexColor;
}