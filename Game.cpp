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
	m_tileMap.reset(LEVEL_ONE);
	Vector2f playerPosition = m_tileMap.coordsToPos(Vector2i(m_tileMap.getSize() - 1, m_tileMap.getSize() - 1));
	m_player = new Character({ (int)playerPosition.x, (int)playerPosition.y, TILE_SIZE, TILE_SIZE }, Character::Type::Player);

	Vector2f npcPosition = m_tileMap.coordsToPos(Vector2i(0, 0));
	m_npc = new Character({ (int)npcPosition.x, (int)npcPosition.y, TILE_SIZE, TILE_SIZE });
	

	m_tileMap.getPath(m_tileMap.posToCoords(npcPosition), m_tileMap.posToCoords(playerPosition));
	return true;
}


void Game::loadContent()
{
	//DEBUG_MSG("Loading Content");
}

void Game::render()
{
	m_renderer.clear();

	m_renderer.render(&m_tileMap);
	m_renderer.render(m_player);
	m_renderer.render(m_npc);

	m_renderer.present();
}

int x = 0;
int y = 0;
int targetX = 0;
int targetY = 0;

void Game::update()
{
	m_framesCount++;
	if (SDL_GetTicks() > m_lastTicks + 1000) //every second
	{
		//set last ticks to the current ticks
		m_lastTicks = SDL_GetTicks(); 

		//calculate fps 
		m_framesPerSecond = m_framesCount;
		std::cout << "FPS: " << m_framesPerSecond << std::endl;
		m_framesCount = 0;

		//update npc
		m_npc->move();
	}
	if (SDL_GetTicks() > testTicks + 25)
	{
		testTicks = SDL_GetTicks();
		if (flip)
		{
			x++;
			if (x == LEVEL_ONE - 1)
			{
				flip = !flip;
				if (flipY)
				{
					y++;
				}
				else
				{
					y--;
				}
				if (y == LEVEL_ONE - 1)
				{
					flipY = !flipY;
					if (targetFlip)
					{
						targetX++;
					}
					else
					{
						targetX--;
					}
					if (targetX == LEVEL_ONE - 1)
					{
						targetFlip = !targetFlip;
						if (targetFlipY)
						{
							targetY++;
						}
						else
						{
							targetY--;
						}
						if (targetY == LEVEL_ONE - 1)
						{
							targetFlipY = !targetFlipY;
						}
					}
				}
			}
		}
		else
		{
			x--;
			if (x == 0)
			{
				flip = !flip;
				if (flipY)
				{
					y++;
				}
				else
				{
					y--;
				}
				if (y == 0)
				{
					flipY = !flipY;
					if (targetFlip)
					{
						targetX++;
					}
					else
					{
						targetX--;
					}
					if (targetX == 0)
					{
						targetFlip = !targetFlip;
						if (targetFlipY)
						{
							targetY++;
						}
						else
						{
							targetY--;
						}
						if (targetY == 0)
						{
							targetFlipY = !targetFlipY;
						}
					}
				}
			}
		}
		m_npc->setPos(Vector2i(x, y));
		m_player->setPos(Vector2i((LEVEL_ONE - 1) - targetX, (LEVEL_ONE - 1) - targetY));
		m_tileMap.getPath(Vector2i((LEVEL_ONE - 1) - targetX, (LEVEL_ONE - 1) - targetY), Vector2i(x, y));
	}
}

void Game::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
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
	delete m_player;
	m_tileMap.cleanUpTiles();
	SDL_Quit();
}

