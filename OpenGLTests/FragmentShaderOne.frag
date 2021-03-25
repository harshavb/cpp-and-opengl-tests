// Fragment shader that uses a color from a uniform variable

#version 410 core

out vec4 FragColor;
uniform vec4 ourColorUniform;  // A uniform is a global variable that can be changed anywhere outside the shader
	
void main()
{
	FragColor = ourColorUniform;
};