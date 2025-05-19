#include "../Engine/Core/Log.h"
#include "GameApp.h"

int main(int argc, char** argv)
{
	Log::Init();

	AppInfo spec;
	spec.Width = 600.f;
	spec.Height = 800.f;
	spec.Title = "MineBreaker";
	GameApp* game = new GameApp(spec);

	game->Initialize();
	game->Run();

	delete game;
}
