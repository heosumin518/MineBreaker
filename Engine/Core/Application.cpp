#include "pch.h"
#include "Application.h"
#include "Timer.h"
#include "Renderer/Renderer.h"
#include "Scene/SceneManager.h"
#include "Renderer/FontRenderer.h"

#include <filesystem>


Application::Application(const AppInfo& spec)
	: m_Info(spec)
{
	WindowProps windowProps;
	windowProps.Width = spec.Width;
	windowProps.Height = spec.Height;
	windowProps.Title = spec.Title;

	m_Window = std::make_unique<Window>(windowProps);

	m_Timer = std::make_shared<Timer>();
	m_Renderer = std::make_shared<Renderer>(m_Window->GetWidth(), m_Window->GetHeight());
	m_SceneManager = std::make_shared<SceneManager>();
	m_FontRenderer = std::make_shared<FontRenderer>();
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Application::Run() const
{
	GLFWwindow* window = m_Window->GetNativeWindow();

	while (!glfwWindowShouldClose(window))
	{
		m_Timer->Update();
		processInput(window);	// temp

		m_Renderer->BeginRender(m_Window->GetWidth(), m_Window->GetHeight());

		m_SceneManager->Update(m_Timer->GetDeltaTime());
		m_SceneManager->Render();

		// last
		m_Window->Update();
	}
}
