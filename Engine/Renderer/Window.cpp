#include "pch.h"
#include "Window.h"

static uint8_t s_GLFWWindowCount = 0;

Window::Window(const WindowProps& props)
{
	Initialize(props);
}

void Window::Initialize(const WindowProps& props)
{
	m_Data.Title = props.Title;
	m_Data.Width = props.Width;
	m_Data.Height = props.Height;

	CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

	if (s_GLFWWindowCount == 0)
	{
		int success = glfwInit();
		// TODO: glfwInit assert
	}

	m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), props.Title.c_str(), nullptr, nullptr);
	++s_GLFWWindowCount;

	m_Context = std::make_unique<OpenGLContext>(m_Window);
	m_Context->Initialize();


}
