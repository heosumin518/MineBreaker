#pragma once

/**
 * \brief ���� ���� �� ��ȣ����
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

