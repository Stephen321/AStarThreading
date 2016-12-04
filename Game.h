#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Renderer.h""
#include "Character.h"
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
	const int LEVEL_ONE = 30;
	const int LEVEL_TWO = 100;
	const int LEVEL_THREE = 1000;


	//calcluate average of last 10 frame times in order to display average FPS over last second
	Uint32 m_lastTicks; //the last recorded time.
	Uint32 m_framesPerSecond; //the current FPS.
	Uint32 m_framesCount; //frames passed since the last recorded fps.

	Character* m_player;
	Character* m_npc;

	Uint32 testTicks;
	bool flip = true;
	bool flipY = true;
	bool targetFlip = true;
	bool targetFlipY = true;

	TileMap m_tileMap;
};
#endif

