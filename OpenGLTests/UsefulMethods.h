#pragma once
#include <GLFW/glfw3.h>

class UsefulMethods
{
public:
	// Resizes glViewport when window is resized
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	// Processes input (wow ik amazing)
	static void processInput(GLFWwindow* window);
};