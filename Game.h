#ifndef GAME_H
#define GAME_H
#include "Renderer.h"

class Game
{
public:
	Game();
	~Game();
	bool initialize(const char*, int, int, int, int, int);
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
};
#endif

