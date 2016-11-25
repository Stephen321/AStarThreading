#ifndef GAME_H
#define GAME_H
#include "Renderer.h"
#include "Tile.h"

class Game
{
public:
	Game();
	~Game();
	bool initialize(const char* title, int width, int height, int flags);
	void loadContent();
	void unloadContent();
	void render();
	void update();
	void handleEvents();
	bool isRunning();
	void cleanUp();
private:
	Renderer m_renderer;
	bool m_running;

	Tile testTile;
};
#endif

