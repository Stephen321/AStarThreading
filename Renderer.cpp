#include "Renderer.h"

Renderer::Renderer()
	: m_window(NULL)
	, m_renderer(NULL)
{

}


bool Renderer::initialize(const char* title, int width, int height, int flags)
{
	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

	if (m_window != 0)
	{
		//DEBUG_MSG("Window creation success");
		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		if (m_renderer != 0)
		{
			//DEBUG_MSG("Renderer creation success");
			SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
			return true;
		}
		else
		{
			//DEBUG_MSG("Renderer init fail");
			return false;
		}
	}
	else
	{
		//DEBUG_MSG("Window init fail");
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
	setDrawColour(128, 64, 128, 255);
	SDL_RenderPresent(m_renderer);
}

void Renderer::setDrawColour(int r, int g, int b, int a) const
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

void Renderer::setDrawColour(const Colour& c) const
{
	SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
}

void Renderer::render(const Drawable* d) const
{
	d->render(*this);
}

void Renderer::drawRect(const SDL_Rect& r, const Colour& fillColour, const Colour& outlineColour) const
{
	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
	setDrawColour(fillColour);
	SDL_RenderFillRect(m_renderer, &r);
	setDrawColour(outlineColour);
	SDL_RenderDrawRect(m_renderer, &r);

}

