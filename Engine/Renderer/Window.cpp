#include "pch.h"
#include "Window.h"

static uint8_t s_GLFWWindowCount = 0;

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::Window(const WindowProps& props)
{
	Initialize(props);
}

Window::~Window()
{
	Shutdown();
	CORE_INFO("Close {} window..", m_Data.Title);
}

void Window::OnUpdate()
{
	glfwPollEvents();
	m_Context->SwapBuffers();
}

void Window::SetVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	m_Data.VSync = enabled;
}

void Window::Initialize(const WindowProps& props)
{
	m_Data.Title = props.Title;
	m_Data.Width = props.Width;
	m_Data.Height = props.Height;

	CORE_INFO("Creating window {} ({}, {})", props.Title, props.Width, props.Height);

	if (s_GLFWWindowCount == 0)
	{
		int success = glfwInit();
		// TODO: glfwInit assert
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), props.Title.c_str(), nullptr, nullptr);
	if (m_Window == nullptr)
	{
		CORE_ERROR("Failed to create GLFW window");
		glfwTerminate();
		return;
	}
	++s_GLFWWindowCount;

	m_Context = std::make_unique<OpenGLContext>(m_Window);
	m_Context->Initialize();

	SetVSync(true);

	//glViewport(0, 0, props.Width, props.Height);

	// 윈도우 리사이징
	glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);

	// TODO: 이벤트 등록
}

void Window::Shutdown()
{
	glfwDestroyWindow(m_Window);
	--s_GLFWWindowCount;

	if (s_GLFWWindowCount == 0)
	{
		glfwTerminate();
	}
}
