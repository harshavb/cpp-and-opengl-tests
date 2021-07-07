#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
using namespace std;

class UsefulMethods
{
public:
	// Resizes glViewport when window is resized
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	// Checks input to update several things
	static void processInput(GLFWwindow* window);
	static float processMixing(GLFWwindow* window, float mixPercent);
	static glm::vec3 processCameraPosition(GLFWwindow* window, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);

	// Checks mouse for camera rotation and zoom
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xpos, double ypos);

	static glm::vec3 getCameraFront() { return cameraFront; }
	static float getFov() { return fov; }

private:
	static float deltaTime, lastFrame, lastX, lastY, yaw, pitch, fov;
	static bool firstMouse;
	static glm::vec3 cameraFront;
};