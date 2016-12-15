#include <iostream>
#include <thread>
#include <string>

#include <SDL.h>

#include "Game.h"

using namespace std;

int getTileLimitedSize(int resolution)
{
	return ((resolution / WorldConstants::TILE_SIZE) * WorldConstants::TILE_SIZE);
}

int main(int argc, char** argv)
{
	Game* game = new Game();

	DEBUG_MSG("Game Initialising");
	int width = 1280; //set to 1250 if 1260, 1300 if 1280. the window is can always fit a certain amount of tiles completely
	int height = 800;
	if (width - getTileLimitedSize(width) > WorldConstants::TILE_SIZE / 2)
	{
		width = getTileLimitedSize(width) + WorldConstants::TILE_SIZE;
	}
	else
	{
		width = getTileLimitedSize(width);
	}
	if (height - getTileLimitedSize(height) > WorldConstants::TILE_SIZE / 2)
	{
		height = getTileLimitedSize(height) + WorldConstants::TILE_SIZE;
	}
	else
	{
		height = getTileLimitedSize(height);
	}

	game->initialize("DGPP Skelatol", width, height, SDL_WINDOW_INPUT_FOCUS);
	
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


