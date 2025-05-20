#pragma once
#include "Renderer/Window.h"
#include <memory>
#include <string>

class FontRenderer;
class SceneManager;
class Renderer;
class Timer;

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

	virtual void Initialize() = 0;
	void Run() const;

protected:
	std::shared_ptr<Timer> m_Timer;
	std::shared_ptr<Renderer> m_Renderer;
	std::shared_ptr<SceneManager> m_SceneManager;
	std::shared_ptr<FontRenderer> m_FontRenderer;

private:
	AppInfo m_Info;
	std::unique_ptr<Window> m_Window;
};
