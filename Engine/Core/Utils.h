#pragma once
#include "glm/vec2.hpp"
#include "Renderer/Window.h"

glm::vec2 GetMouseWorldPosition(GLFWwindow* window)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	// OpenGL�� 2D ��ǥ��� ���� ���ϴ��� (0,0)
	float worldX = static_cast<float>(mouseX);
	float worldY = static_cast<float>(height - mouseY); // Y�� ������

	return glm::vec2(worldX, worldY);
}
