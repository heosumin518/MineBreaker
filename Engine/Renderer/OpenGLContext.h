#pragma once
#include <glad/glad.h>
#include "GLFW/glfw3.h"

/**
 * \brief OpenGL 컨텍스트 관리
 */
class OpenGLContext
{
public:
	OpenGLContext(GLFWwindow* windowHandle);

	void Initialize();
	void SwapBuffers();

private:
	GLFWwindow* m_WindowHandle;
};

