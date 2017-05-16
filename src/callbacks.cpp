#ifndef CALLBACKS
#define CALLBACKS
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)

	{
		std::cout << "Escape From Window" << std::endl;

		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	GLfloat cameraSpeed = 0.05f;
	if (key == GLFW_KEY_W)
		cameraPos += cameraSpeed * cameraFront;
	if (key == GLFW_KEY_S)
		cameraPos -= cameraSpeed * cameraFront;
	if (key == GLFW_KEY_A)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (key == GLFW_KEY_D)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
#endif // CALLBACKS