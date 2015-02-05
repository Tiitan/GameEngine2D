#include "Engine/Game.h"
#include "MapHexa.h"
#include "SceneTestMap.h"

int main()
{
	Engine::Game game(640, 480, "test");
	SceneTestMap scene;

	game.AddScene(&scene);
	game.Init();
	game.MainLoop();
}