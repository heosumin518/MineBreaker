#include "../Engine/Core/Log.h"
#include "GameApp.h"

int main(int argc, char** argv)
{
	Log::Init();

	const std::string name = "MineBreaker";
	GameApp* game = new GameApp(name);

	game->Run();

	delete game;
}
