#include "UsefulMethods.h"

// Resizes glViewport when window is resized
void UsefulMethods::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Processes input (wow ik amazing)
void UsefulMethods::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
