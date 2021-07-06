#include "UsefulMethods.h"

float UsefulMethods::deltaTime = 0.0f;
float UsefulMethods::lastFrame = 0.0f;

// Resizes glViewport when window is resized
void UsefulMethods::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Processes input (moved inside test classes starting at TestEight and afterwards)
void UsefulMethods::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

float UsefulMethods::processMixing(GLFWwindow* window, float mixPercent)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if (mixPercent < 1.0f) return mixPercent + 0.001f;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if (mixPercent > 0.0f) return mixPercent - 0.001f;
	}

	return mixPercent;
}

glm::vec3 UsefulMethods::processCameraPosition(GLFWwindow* window, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
{
	float currentFrame = glfwGetTime();
	UsefulMethods::deltaTime = currentFrame - UsefulMethods::lastFrame;
	UsefulMethods::lastFrame = currentFrame;

	const float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		return cameraPos + cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		return cameraPos - cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		return cameraPos - glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		return cameraPos + glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	return cameraPos;
}
