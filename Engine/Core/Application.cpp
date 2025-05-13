#include "pch.h"
#include "Application.h"

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

	while (!glfwWindowShouldClose(window))
	{
		// TODO: Manager Update
		// TODO: Run Actual Game Code;

		m_Window->OnUpdate();
	}
}
