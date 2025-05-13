#pragma once
#include <string>
#include "Core/Application.h"

class GameApp : public Application
{
public:
	GameApp(const AppInfo& spec)
		: Application(spec)
	{
	}
};
