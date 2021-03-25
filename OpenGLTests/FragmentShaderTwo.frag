// Another GLSL shader that outputs a FragColor based on a previously inputted color from a vertex shader

#version 410 core

out vec4 FragColor;
in vec3 ourColor;

void main()
{
	FragColor = vec4(ourColor, 1.0f);
}