#include "pch.h"
#include "Application.h"
#include "Timer.h"

Application::Application(const std::string& applicationName)
	: m_Name(applicationName)
{
	WindowProps windowProps;
	windowProps.Width = 800;
	windowProps.Height = 600;
	windowProps.Title = applicationName;

	m_Window = std::make_unique<Window>(windowProps);
}

void Application::Run()
{
	GLFWwindow* window = m_Window->GetNativeWindow();

	Timer timer;

	while (!glfwWindowShouldClose(window))
	{
		// TODO: Manager Update
		// TODO: Run Actual Game Code;
		timer.OnUpdate();

		m_Window->OnUpdate();
	}
}
