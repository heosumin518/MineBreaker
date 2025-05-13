#pragma once
#include "Renderer/Window.h"
#include <memory>

/**
 * \brief ���� ���� �� ��ȣ����
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

