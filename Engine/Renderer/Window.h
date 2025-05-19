#pragma once
#include "OpenGLContext.h"
#include <memory>

struct WindowProps
{
	std::string Title;
	uint32_t Width;
	uint32_t Height;

	WindowProps(const std::string& title = "My Engine",
		uint32_t width = 800,
		uint32_t height = 600)
		: Title(title), Width(width), Height(height)
	{
	}
};

class Window
{
public:
	Window(const WindowProps& props);
	virtual ~Window();

	void Update();

	unsigned int GetWidth() const { return m_Data.Width; }
	unsigned int GetHeight() const { return m_Data.Height; }

	void SetVSync(bool enabled);
	bool IsVSync() const { return m_Data.VSync; }

	GLFWwindow* GetNativeWindow() const { return m_Window; }


private:
	void Initialize(const WindowProps& props);
	void Shutdown();

private:
	GLFWwindow* m_Window;
	std::unique_ptr<OpenGLContext> m_Context;

	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
	};

	WindowData m_Data;
};
