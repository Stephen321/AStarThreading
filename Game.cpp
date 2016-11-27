#include <Game.h>
#include <iostream>
#include <thread>


Game::Game() 
	: m_running(false)
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
	m_tileMap.reset(SIZE_ONE);

	
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

	m_renderer.present();
}

void Game::update()
{
	//DEBUG_MSG("Updating....");
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
	m_tileMap.cleanUpTiles();
	SDL_Quit();
}