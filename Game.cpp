#include <Game.h>
#include <iostream>
#include <thread>


Game::Game() 
	: m_running(false)
	, m_framesCount(0)
	, m_framesPerSecond(0)
	, m_lastTicks(SDL_GetTicks())
{
}

Game::~Game()
{
}


bool Game::initialize(const char* title, int width, int height, int flags)
{
	srand(time(NULL));
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		DEBUG_MSG("SDL Init success");
		if (!m_renderer.initialize(title, width, height, flags))
		{
			return false;
		}
	}
	else
	{
		DEBUG_MSG("SDL init fail");
		return false;
	}
	m_running = true;
	

	//initialize game
	m_tileMap.reset(TileMap::MEDIUM);
	resetChars();
	setNewPlayerTarget();
	//m_tileMap.getPath(Helper::posToCoords(m_npcs[29].getPos()), Helper::posToCoords(m_player.getPos()));
	return true;
}

void Game::resetChars()
{
	const LevelData levelData = WorldConstants::levels[m_tileMap.getSize()]; //current level data
	int charSpawnWidth = levelData.getCharSpawnWidth();
	int npcCount = levelData.getNpcCount();

	//player positioned randomly between (0, charSpawnWidth) -> (0, levelHeight - charSpawnWidth)
	Vector2f playerPosition = Helper::coordsToPos(Vector2i(rand() % charSpawnWidth, charSpawnWidth + (rand() % (int)(m_tileMap.getLength() - charSpawnWidth - 1))));
	m_player = Character(playerPosition, Character::Type::Player);

	//position npcs
	m_npcs.clear();
	int xOffset = m_tileMap.getLength() - charSpawnWidth;
	int yOffset = rand() % charSpawnWidth;
	bool indent = true;
	for (int i = 0; i < npcCount; i++)
	{
		Vector2f pos = Helper::coordsToPos(Vector2i(xOffset, yOffset));
		xOffset += 2;
		if (xOffset >= m_tileMap.getLength())
		{
			xOffset = m_tileMap.getLength() - charSpawnWidth;
			yOffset++;
			if (indent)
			{
				xOffset++;
			}
			indent = !indent;
		}
		m_npcs.push_back(Character(pos));
	}
}

void Game::loadContent()
{
	//DEBUG_MSG("Loading Content");
}

void Game::render()
{
	m_renderer.clear();

	m_renderer.render(&m_tileMap);
	m_renderer.render(&m_player);
	for (const Character& npc : m_npcs)
	{
		m_renderer.render(&npc);
	}

	m_renderer.present();
}

int x = 0;
int y = 0;
int targetX = 0;
int targetY = 0;

void Game::update()
{
	m_capTimer.start();
	m_framesCount++;
	if (LTimer::gameTime() > m_lastTicks + 1000) //every second
	{
		//set last ticks to the current ticks
		m_lastTicks = LTimer::gameTime();

		//calculate fps 
		m_framesPerSecond = m_framesCount;
		//std::cout << "FPS: " << m_framesPerSecond << std::endl;
		m_framesCount = 0;
	}

	if (LTimer::gameTime() > m_charUpdateTicks + WorldConstants::TICKS_PER_CHAR_UPDATE) 
	{
		//set last ticks to the current ticks
		m_charUpdateTicks = LTimer::gameTime();
		for (Character& npc : m_npcs)
		{
			npc.move();
		}
		m_player.move();
	}

	if (m_player.remainingPathPoints() == 0)
	{
		setNewPlayerTarget();
	}

	int frameTicks = m_capTimer.getTicks();//time since start of frame
	if (frameTicks < WorldConstants::TICKS_PER_FRAMES)
	{
		//Wait remaining time before going to next frame
		SDL_Delay(WorldConstants::TICKS_PER_FRAMES - frameTicks);
	}
}

void Game::setNewPlayerTarget()
{
	//get random target for player within how ever many moves the player makes before we next update its path (TICKS_PER_PLAYER_UPDATE / 1000)
	Vector2i currentCoords = Helper::posToCoords(m_player.getPos());
	Vector2i target(Helper::random(currentCoords.x - WorldConstants::MAX_P_TARGET_MOVES, currentCoords.x + WorldConstants::MAX_P_TARGET_MOVES),
					Helper::random(currentCoords.y - WorldConstants::MAX_P_TARGET_MOVES, currentCoords.y + WorldConstants::MAX_P_TARGET_MOVES));
	while (m_tileMap.getTypeAt(target) == Tile::Type::Wall)
	{
		target = Vector2i(Helper::random(currentCoords.x - WorldConstants::MAX_P_TARGET_MOVES, currentCoords.x + WorldConstants::MAX_P_TARGET_MOVES),
						  Helper::random(currentCoords.y - WorldConstants::MAX_P_TARGET_MOVES, currentCoords.y + WorldConstants::MAX_P_TARGET_MOVES));
	}
	target.x = Helper::clamp(target.x, 0, m_tileMap.getLength());
	target.y = Helper::clamp(target.y, 0, m_tileMap.getLength());
	m_player.setTilePath(m_tileMap.getPath(currentCoords, target));
}

void Game::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				m_running = false;
				break;
			case SDLK_UP:
				m_renderer.moveCamera(0, -1);
				break;
			case SDLK_DOWN:
				m_renderer.moveCamera(0, 1);
				break;
			case SDLK_LEFT:
				m_renderer.moveCamera(-1, 0);
				break;
			case SDLK_RIGHT:
				m_renderer.moveCamera(1, 0);
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEWHEEL:
			if (event.wheel.y < 0)
			{
				m_renderer.zoom(1);
			}
			else if (event.wheel.y > 0)
			{
				m_renderer.zoom(-1);
			}
			break;
		}
	}
}

bool Game::isRunning()
{
	return m_running;
}

void Game::unloadContent()
{
	DEBUG_MSG("Unloading Content");
}

void Game::cleanUp()
{
	DEBUG_MSG("Cleaning Up");
	m_renderer.cleanUp();
	m_npcs.clear();
	m_tileMap.cleanUpTiles();
	SDL_Quit();
}
