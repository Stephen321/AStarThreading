#ifndef GAME_H
#define GAME_H
#include "Renderer.h"
#include "TileMap.h"

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
	const int SIZE_ONE = 10;
	const int SIZE_TWO = 100;
	const int SIZE_THREE = 1000;

	TileMap m_tileMap;
};
#endif

