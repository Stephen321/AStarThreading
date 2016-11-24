#include "Renderer.h"

Renderer::Renderer()
	: m_window(NULL)
	, m_renderer(NULL)
{

}


void Renderer::initialize()
{
	m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

	if (m_window != 0)
	{
		DEBUG_MSG("Window creation success");
		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		if (m_p_Renderer != 0)
		{
			DEBUG_MSG("Renderer creation success");
			SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		}
		else
		{
			DEBUG_MSG("Renderer init fail");
			return false;
		}
	}
	else
	{
		DEBUG_MSG("Window init fail");
		return false;
	}
}

void Renderer::cleanUp()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
}

void Renderer::clear()
{
	SDL_RenderClear(m_renderer);
}

void Renderer::present()
{
	SDL_RenderPresent(m_renderer);
}

void Renderer::setDrawColor(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

