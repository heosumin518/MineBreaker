#include "pch.h"
#include "Application.h"
#include "Timer.h"
#include "Renderer/Renderer.h"

Application::Application(const ApplicationSpecification& spec)
	: m_Specification(spec)
{
	WindowProps windowProps;
	windowProps.Width = spec.Width;
	windowProps.Height = spec.Height;
	windowProps.Title = spec.Title;

	m_Window = std::make_unique<Window>(windowProps);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Application::Run()
{
	GLFWwindow* window = m_Window->GetNativeWindow();

	Timer timer;
	Renderer renderer(m_Window->GetWidth(), m_Window->GetHeight());

	while (!glfwWindowShouldClose(window))
	{
		timer.OnUpdate();

		processInput(window);	// temp
		renderer.OnUpdate();

		m_Window->OnUpdate();
	}
}
