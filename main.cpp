#include <iostream>
#include <thread>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include <Game.h>
#include <Player.h>

using namespace std;

int main(int argc, char** argv)
{
	Game* game = new Game();

	DEBUG_MSG("Game Initialising");
	game->initialize("DGPP Skelatol", 1280, 720, SDL_WINDOW_INPUT_FOCUS);
	
	DEBUG_MSG("Loading Content");
	game->loadContent();


	DEBUG_MSG("Game Loop Starting......");
	while(game->isRunning())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	DEBUG_MSG("Calling Cleanup");
	game->cleanUp();
	game->unloadContent();
	
	return 0;
}


