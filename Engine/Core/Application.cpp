#include "pch.h"
#include "Application.h"
#include "Timer.h"
#include "Renderer/Renderer.h"

Application::Application(const std::string& applicationName)
	: m_Name(applicationName)
{
	WindowProps windowProps;
	windowProps.Width = 800;
	windowProps.Height = 600;
	windowProps.Title = applicationName;

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
	Renderer renderer;

	while (!glfwWindowShouldClose(window))
	{
		// TODO: Manager Update
		// TODO: Run Actual Game Code;
		timer.OnUpdate();
		renderer.OnUpdate();

		processInput(window);

		m_Window->OnUpdate();
	}
}
