#pragma once
#include "Core/Application.h"
#include <string>

class GameApp : public Application
{
public:
	GameApp(const AppInfo& spec)
		: Application(spec)
	{
	}

	void Initialize() override;
};
