#include "pch.h"
#include "OpenGLContext.h"

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_WindowHandle(windowHandle)
{
	// TODO window handle assert
}

void OpenGLContext::Initialize()
{
	glfwMakeContextCurrent(m_WindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	// TODO glad init assert

	CORE_INFO("OpenGL Info:");
	CORE_INFO("  Vendor: {}", (const char*)glGetString(GL_VENDOR));
	CORE_INFO("  Renderer: {}", (const char*)glGetString(GL_RENDERER));
	CORE_INFO("  Version: {}", (const char*)glGetString(GL_VERSION));
}

void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}

