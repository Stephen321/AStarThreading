#ifndef GAME_H
#define GAME_H
#include <vector>
#include "LTimer.h"
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
	void resetChars();
	void setNewPlayerTarget();

	Renderer m_renderer;
	bool m_running;

	//calcluate average of last 10 frame times in order to display average FPS over last second
	Uint32 m_lastTicks; //the last recorded time.
	Uint32 m_framesPerSecond; //the current FPS.
	Uint32 m_framesCount; //frames passed since the last recorded fps.

	LTimer m_capTimer;

	Uint32 m_charUpdateTicks;


	Character m_player;
	std::vector<Character> m_npcs;

	bool flip = true;
	bool flipY = true;
	bool targetFlip = true;
	bool targetFlipY = true;

	TileMap m_tileMap;
};
#endif

