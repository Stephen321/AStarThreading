#include "Game.h"
#include <iostream>


Game::Game() 
	: m_running(false)
	, m_framesCount(0)
	, m_framesPerSecond(0)
	, m_lastTicks(SDL_GetTicks())
{
	AStar::setTileMap(&m_tileMap); //make sure AStar has a pointer to tileMap

	std::cout << "Display path lines: " << DISPLAY_LINES << std::endl;
	std::cout << "Using threads: " << USE_THREADS << std::endl;
	std::cout << "Display fps: " << DISPLAY_FPS << std::endl;
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
	return true;
}

void Game::reset(TileMap::Size size)
{
	AStar::reset();
	if (USE_THREADS)
		ThreadPool::getInstance().stop(); //stop running threads and clear job queue
	m_tileMap.reset(size);
	if (USE_THREADS)
		ThreadPool::getInstance().start(); //start threads again now that the tile map and characters has been changed
	resetChars();
	m_renderer.resetCamera();
}

void Game::resetChars()
{
	const LevelData levelData = WorldConstants::levels[m_tileMap.getSize()]; //current level data
	int charSpawnWidth = levelData.getCharSpawnWidth();
	int npcCount = levelData.getNpcCount();

	//player positioned randomly between (0, charSpawnWidth) -> (0, levelHeight - charSpawnWidth)
	Vector2f playerPosition = Helper::coordsToPos(Vector2i(rand() % charSpawnWidth, charSpawnWidth + (rand() % (int)(m_tileMap.getLength() - charSpawnWidth - 1))));
	if (m_player != 0)
	{
		delete m_player;
		m_player = 0;
	}
	m_player = new Character(playerPosition, Character::Type::Player);
	m_player->clearTilePath();

	//position npcs
	cleanUpNpcs();
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
		m_npcs.push_back(new Character(pos, GameObject::Type::NPC, m_player));
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
	if (DISPLAY_LINES)
	{
		AStar::render(m_renderer);
	}
	m_renderer.render(m_player);
	for (const Character* npc : m_npcs)
	{
		m_renderer.render(npc);
	}
	m_renderer.present();
}

int x = 0;
int y = 0;
int targetX = 0;
int targetY = 0;

void Game::update()
{
	m_framesCount++;
	if (LTimer::gameTime() > m_lastTicks + 1000) //every second
	{
		//set last ticks to the current ticks
		m_lastTicks = LTimer::gameTime();

		//calculate fps 
		m_framesPerSecond = m_framesCount;
		if (DISPLAY_FPS)
		{
			std::cout << "FPS: " << m_framesPerSecond << std::endl;
		}
		m_framesCount = 0;
	}

	if (LTimer::gameTime() > m_playerUpdateTicks + WorldConstants::TICKS_PER_PLAYER_UPDATE)
	{
		//set last ticks to the current 
		m_playerUpdateTicks = LTimer::gameTime();
		m_player->move();
	}

	if (LTimer::gameTime() > m_npcUpdateTicks + WorldConstants::TICKS_PER_NPC_UPDATE)
	{
		//set last ticks to the current ticks
		m_npcUpdateTicks = LTimer::gameTime();
		for (Character* npc : m_npcs)
		{
			npc->move();
		}
	}

	if (m_player->remainingPathPoints() == 0)
	{
		AStar::removePoints(m_player);
		AStar::FindPath(m_player, getNewPlayerTarget());
	}

	for (std::vector<Character*>::iterator it = m_npcs.begin(); it != m_npcs.end();)
	{
		if (Helper::posToCoords((*it)->getPos()) == Helper::posToCoords(m_player->getPos()))
		{
			AStar::removePoints((*it));
			delete (*it);
			(*it) = 0;
			it = m_npcs.erase(it);
		}
		else
		{
			++it;
		}
	}
	if (m_npcs.size() == 0)
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
}

Vector2i Game::getNewPlayerTarget()
{
	//get random target for player within how ever many moves the player makes before we next update its path (TICKS_PER_PLAYER_UPDATE / 1000)
	Vector2i currentCoords = Helper::posToCoords(m_player->getPos());
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
		case SDL_QUIT:
			m_running = false;
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_1:
				m_currentSize = TileMap::SMALL;
				reset(m_currentSize);
				break;
			case SDLK_2:
				m_currentSize = TileMap::MEDIUM;
				reset(m_currentSize);
				break;
			//case SDLK_3:
			//	m_currentSize = TileMap::LARGE;
			//	reset(m_currentSize);
			//	break; 
			case SDLK_l:
				DISPLAY_LINES = !DISPLAY_LINES;
				std::cout << "Display path lines: " << DISPLAY_LINES << std::endl;
				break;
			case SDLK_t:
				USE_THREADS = !USE_THREADS;
				std::cout << "Using threads: " << USE_THREADS << std::endl;
				break;
			case SDLK_f:
				DISPLAY_FPS = !DISPLAY_FPS;
				std::cout << "Display fps: " << DISPLAY_FPS << std::endl;
				break;
			default:
				break;
			}
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
	if (m_player != 0)
	{
		delete m_player;
		m_player = 0;
	}
	cleanUpNpcs();
	if (USE_THREADS)
		ThreadPool::getInstance().cleanUp();
	m_tileMap.cleanUpTiles();
	SDL_Quit();
}

void Game::cleanUpNpcs()
{
	for (int i = 0; i < m_npcs.size(); i++)
	{
		delete m_npcs[i];
		m_npcs[i] = 0;
	}
	m_npcs.clear();
}
