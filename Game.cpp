#include <Game.h>
#include <iostream>
#include <thread>


Game::Game() : m_running(false)
{
}

Game::~Game()
{
}

bool Game::initialize(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		DEBUG_MSG("SDL Init success");
		return m_renderer.initialize();
	}
	else
	{
		DEBUG_MSG("SDL init fail");
		return false;
	}
	m_running = true;
	

	//initialize game

	return true;
}



void Game::loadContent()
{
	//DEBUG_MSG("Loading Content");
}

void Game::render()
{
	m_renderer.clear();

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
					DEBUG_MSG("Up Key Pressed");
					m_renderer.setDrawColor(255, 0, 0, 255);
					break;
				case SDLK_DOWN:
					DEBUG_MSG("Down Key Pressed");
					m_renderer.setDrawColor(0, 255, 0, 255);
					break;
				case SDLK_LEFT:
					DEBUG_MSG("Left Key Pressed");
					m_renderer.setDrawColor(0, 0, 255, 255);
					break;
				case SDLK_RIGHT:
					DEBUG_MSG("Right Key Pressed");
					m_renderer.setDrawColor(255, 255, 255, 255);
					break;
				default:
					m_renderer.setDrawColor(0, 0, 0, 255);
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
	SDL_Quit();
}
