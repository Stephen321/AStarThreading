#include <iostream>
#include <thread>
#include <string>

#include <TinyXML2.h>

#include <SDL.h>
#include <SDL_image.h>

#include <Game.h>
#include <Player.h>

using namespace std;
using namespace tinyxml2;

int main(int argc, char** argv){

	DEBUG_MSG("Game Object Created");

	Player* player = new Player();

	Game* game = new Game();

	DEBUG_MSG("Game Initialising");
	game->initialize("DGPP Skelatol",300,100,800,600, SDL_WINDOW_INPUT_FOCUS);
	
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


