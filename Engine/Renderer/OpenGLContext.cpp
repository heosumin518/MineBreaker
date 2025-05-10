#include "pch.h"
#include "OpenGLContext.h"

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_WindowHandle(windowHandle)
{
}

void OpenGLContext::Initialize()
{

}

void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}

