#include "../Engine/Core/Log.h"
#include "GameApp.h"

int main(int argc, char** argv)
{
	Log::Init();

	ApplicationSpecification spec;
	spec.Width = 800.f;
	spec.Height = 600.f;
	spec.Title = "MineBreaker";
	GameApp* game = new GameApp(spec);

	game->Run();

	delete game;
}
