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
	m_player = new Player({(int)playerPosition.x, (int)playerPosition.y, TILE_SIZE, TILE_SIZE});

	
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

	m_renderer.present();
}

void Game::update()
{
	m_framesCount++;
	if (m_lastTicks < SDL_GetTicks() - 1000)
	{
		m_lastTicks = SDL_GetTicks();
		m_framesPerSecond = m_framesCount;
		std::cout << "FPS: " << m_framesPerSecond << std::endl;
		m_framesCount = 0;
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

