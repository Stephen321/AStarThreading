#include <Game.h>
#include <iostream>
#include <thread>


Game::Game() 
	: m_running(false)
	, m_framesCount(0)
	, m_framesPerSecond(0)
	, m_lastTicks(SDL_GetTicks())
	, m_nowPerfromCounter(SDL_GetPerformanceCounter())
	, m_lastPerformCounter(0)
	, m_deltaTime(0)
{
	AStar::setTileMap(&m_tileMap); //make sure AStar has a pointer to tileMap
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
	m_currentSize = TileMap::SMALL;
	reset(m_currentSize);
	//AStar::setCharacterPath(m_tileMap, &m_player, Helper::posToCoords(m_player.getPos()), getNewPlayerTarget());
	return true;
}

void Game::reset(TileMap::Size size)
{
	ThreadPool::getInstance().stop(); //stop running threads and clear job queue
	m_tileMap.reset(size);
	resetChars();
	ThreadPool::getInstance().start(); //start threads again now that the tile map and characters has been changed
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


	for (Character& c : m_npcs)
	{
		ThreadPool::getInstance().addJob(std::bind(&AStar::setCharacterPath, &c, Helper::posToCoords(c.getPos()), Helper::posToCoords(m_player.getPos())));
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
		//TODO: put this back in and have player update to follow
		//AStar::setCharacterPath(m_tileMap, &m_player, Helper::posToCoords(m_player.getPos()), getNewPlayerTarget());
	}


	m_lastPerformCounter = m_nowPerfromCounter;
	m_nowPerfromCounter = SDL_GetPerformanceCounter();
	m_deltaTime = (double)((m_nowPerfromCounter - m_lastPerformCounter) * 1000 / SDL_GetPerformanceFrequency());

	for (Character& npc : m_npcs)
	{
		npc.update(m_deltaTime);
	}
	m_player.update(m_deltaTime);


	//TODO: better check
	bool levelOver = true;
	for (Character& c : m_npcs)
	{
		if (Helper::posToCoords(c.getPos()) != Helper::posToCoords(m_player.getPos()))
		{
			levelOver = false;
			break;
		}
	}
	if (levelOver)
	{
		if (m_currentSize + 1 < WorldConstants::LEVEL_COUNT)
		{
			m_currentSize = (TileMap::Size)(m_currentSize + 1);
		}
		else
		{
			m_currentSize = (TileMap::Size)0;
		}
		reset(m_currentSize);
	}

	int frameTicks = m_capTimer.getTicks();//time since start of frame
	if (frameTicks < WorldConstants::TICKS_PER_FRAMES)
	{
		//Wait remaining time before going to next frame
		SDL_Delay(WorldConstants::TICKS_PER_FRAMES - frameTicks);
	}
}

Vector2i Game::getNewPlayerTarget()
{
	//get random target for player within how ever many moves the player makes before we next update its path (TICKS_PER_PLAYER_UPDATE / 1000)
	Vector2i currentCoords = Helper::posToCoords(m_player.getPos());
	Vector2i target(Helper::random(currentCoords.x - WorldConstants::MAX_P_TARGET_MOVES, currentCoords.x + WorldConstants::MAX_P_TARGET_MOVES),
					Helper::random(currentCoords.y - WorldConstants::MAX_P_TARGET_MOVES, currentCoords.y + WorldConstants::MAX_P_TARGET_MOVES));
	target.x = Helper::clamp(target.x, 0, m_tileMap.getLength());
	target.y = Helper::clamp(target.y, 0, m_tileMap.getLength());
	while (m_tileMap.getTypeAt(target) == Tile::Type::Wall)
	{
		target = Vector2i(Helper::random(currentCoords.x - WorldConstants::MAX_P_TARGET_MOVES, currentCoords.x + WorldConstants::MAX_P_TARGET_MOVES),
						  Helper::random(currentCoords.y - WorldConstants::MAX_P_TARGET_MOVES, currentCoords.y + WorldConstants::MAX_P_TARGET_MOVES));
		target.x = Helper::clamp(target.x, 0, m_tileMap.getLength());
		target.y = Helper::clamp(target.y, 0, m_tileMap.getLength());
	}

	return target;
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
	ThreadPool::getInstance().cleanUp();
	m_tileMap.cleanUpTiles();
	SDL_Quit();
}
