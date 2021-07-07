#include "UsefulMethods.h"

float UsefulMethods::deltaTime = 0.0f;
float UsefulMethods::lastFrame = 0.0f;
float UsefulMethods::lastX = 400, UsefulMethods::lastY = 300;
float UsefulMethods::yaw = -90.0f;
float UsefulMethods::pitch = 0.0f;
float UsefulMethods::fov = 45.0f;
bool UsefulMethods::firstMouse = true;
glm::vec3 UsefulMethods::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

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
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	float cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		cameraSpeed = 6.0f * deltaTime;
	else
		cameraSpeed = 3.0f * deltaTime;

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

void UsefulMethods::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	// Prevents a teleporting camera when the mouse enters the window for the first time
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	// Calculates mouse offset
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	// Sets and uses factor by which camera is offset
	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

void UsefulMethods::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 103.0f)
		fov = 103.0f;
}