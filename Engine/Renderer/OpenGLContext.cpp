#include "pch.h"
#include "OpenGLContext.h"

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_WindowHandle(windowHandle)
{
}

void OpenGLContext::Initialize()
{
	glfwMakeContextCurrent(m_WindowHandle);
}

void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}

