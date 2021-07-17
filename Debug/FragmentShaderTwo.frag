// Another GLSL shader that outputs a FragColor based on a previously inputted color from a vertex shader

#version 410 core

in vec3 ourColor;
out vec4 FragColor;

void main()
{
	FragColor = vec4(ourColor, 1.0f);
}