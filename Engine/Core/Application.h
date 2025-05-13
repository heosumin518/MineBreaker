#pragma once
#include "Renderer/Window.h"
#include <memory>

/**
 * \brief 엔진 루프 및 상호조정
 */
class Application
{
public:
	Application(const std::string& applicationName);

	void Run();

private:
	std::string m_Name;
	std::unique_ptr<Window> m_Window;
};

