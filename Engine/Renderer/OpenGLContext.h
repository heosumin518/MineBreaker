#pragma once
#include <glad/glad.h>
#include "GLFW/glfw3.h"

/**
 * \brief OpenGL ���ؽ�Ʈ ����
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

