#pragma once
#include <string>
#include "Core/Application.h"

class GameApp : public Application
{
public:
	GameApp(const ApplicationSpecification& spec)
		: Application(spec)
	{
	}
};
