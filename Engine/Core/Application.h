#pragma once
#include "Renderer/Window.h"
#include <memory>

struct AppInfo
{
	std::string Title;
	uint32_t Width;
	uint32_t Height;
};

/**
 * \brief 엔진 루프 및 상호조정
 */
class Application
{
public:
	Application(const AppInfo& spec);

	void Run();

private:
	AppInfo m_Info;
	std::unique_ptr<Window> m_Window;
};

