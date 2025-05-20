#pragma once
#include "glm/vec2.hpp"
#include "Renderer/Window.h"

glm::vec2 GetMouseWorldPosition(GLFWwindow* window)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	// OpenGL의 2D 좌표계는 보통 좌하단이 (0,0)
	float worldX = static_cast<float>(mouseX);
	float worldY = static_cast<float>(height - mouseY); // Y축 뒤집기

	return glm::vec2(worldX, worldY);
}
