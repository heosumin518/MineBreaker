#pragma once
#include <string>
#include "Core/Application.h"

class GameApp : public Application
{
public:
	GameApp(std::string name)
		: Application(name)
	{
	}
};
