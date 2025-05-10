#pragma once

/**
 * \brief 엔진 루프 및 상호조정
 */
class Application
{
public:
	Application(const std::string& applicationName);

private:
	void Run();

private:
	std::string m_Name;
};

