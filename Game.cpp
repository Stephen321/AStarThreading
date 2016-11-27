#include <Game.h>
#include <iostream>
#include <thread>


Game::Game() 
	: m_running(false)
	, m_size(0)
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
	setUpTiles(SIZE_ONE);

	
	return true;
}

void Game::setUpTiles(int size)
{
	m_size = size;
	cleanUpTiles();
	m_tiles = new Tile*[m_size * m_size];
	Colour c(240, 240, 240, 255);
	SDL_Rect r = { 0, 0, TILE_SIZE, TILE_SIZE };
	for (int y = 0; y < m_size; y++)
	{
		for (int x = 0; x < m_size; x++)
		{
			m_tiles[x + (y * m_size)] = new Tile(x, y, c, r);
			r.x += TILE_SIZE;
		}
		r.x = 0.f;
		r.y += TILE_SIZE;
	}
}



void Game::loadContent()
{
	//DEBUG_MSG("Loading Content");
}

void Game::render()
{
	m_renderer.clear();

	for (int i = 0; i < m_size * m_size; i++)
	{
		m_renderer.render(m_tiles[i]);
	}

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
					m_renderer.moveCamera(0, -1);
					break;
				case SDLK_DOWN:
					DEBUG_MSG("Down Key Pressed");
					m_renderer.moveCamera(0, 1);
					break;
				case SDLK_LEFT:
					DEBUG_MSG("Left Key Pressed");
					m_renderer.moveCamera(-1, 0);
					break;
				case SDLK_RIGHT:
					DEBUG_MSG("Right Key Pressed");
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
	cleanUpTiles();
	SDL_Quit();
}

void Game::cleanUpTiles()
{
	if (m_tiles != 0)
	{
		for (int i = 0; i < m_size * m_size; i++)
		{
			delete m_tiles[i];
		}
		delete m_tiles;
	}
}
