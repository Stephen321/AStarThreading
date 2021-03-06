#include "Renderer.h"

Renderer::Renderer()
	: m_window(NULL)
	, m_renderer(NULL)
	, m_currentZoom(1)
{
}


bool Renderer::initialize(const char* title, int width, int height, int flags)
{
	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	if (m_window != 0)
	{
		m_windowWidth = width;
		m_windowHeight = height;
		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		if (m_renderer != 0)
		{
			m_cameraSize.x = width;
			m_cameraSize.y = height;
			m_cameraBounds.w = m_cameraSize.x / WorldConstants::TILE_SIZE;
			m_cameraBounds.h = m_cameraSize.y / WorldConstants::TILE_SIZE;
			m_camera = { m_cameraBounds.x, m_cameraBounds.y, width, height }; //half the size of the window
			SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
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
	setDrawColour(40, 0, 52, 255);
	SDL_RenderPresent(m_renderer);
}

void Renderer::setDrawColour(int r, int g, int b, int a) const
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

SDL_Renderer* Renderer::getRenderer()
{
	return m_renderer;
}

void Renderer::setDrawColour(const Colour& c) const
{
	SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
}

void Renderer::render(const Drawable* d) const
{
	d->render(*this);
}

void Renderer::drawRect(SDL_Rect r, const Colour& fillColour) const
{
	r = applyCameraTransformation(r);
	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
	setDrawColour(fillColour);
	SDL_RenderFillRect(m_renderer, &r);
	setDrawColour(0,0,0,255);
	SDL_RenderDrawRect(m_renderer, &r);
}

SDL_Rect Renderer::applyCameraTransformation(const SDL_Rect& r) const
{
	float xScale = m_windowWidth / m_camera.w;
	float yScale = m_windowHeight / m_camera.h;

	SDL_Rect transformed = r;
	transformed.x -= m_camera.x;
	transformed.x *= xScale;
	transformed.y -= m_camera.y;

	transformed.y *= yScale;
	transformed.w *= xScale;
	transformed.h *= yScale;
	return transformed;
}

SDL_Point Renderer::applyCameraTransformationPoint(SDL_Point& p)
{
	float xScale = m_windowWidth / m_camera.w;
	float yScale = m_windowHeight / m_camera.h;

	SDL_Point transformed = p;
	transformed.x -= m_camera.x;
	transformed.x *= xScale;
	transformed.y -= m_camera.y;
	transformed.y *= yScale;
	return transformed;
}


void Renderer::moveCamera(int xDir, int yDir)
{
	m_camera.x += xDir * WorldConstants::TILE_SIZE;
	m_camera.y += yDir * WorldConstants::TILE_SIZE;
	m_cameraBounds.x += xDir;
	m_cameraBounds.y += yDir;
}

void Renderer::zoom(int dir)
{
	m_currentZoom += ZOOM_AMOUNT * dir;
	if (m_currentZoom < 0)
	{
		m_currentZoom = 0;
	}
	m_cameraBounds.w = (m_currentZoom * m_cameraSize.x) / WorldConstants::TILE_SIZE;
	m_cameraBounds.h = (m_currentZoom * m_cameraSize.y) / WorldConstants::TILE_SIZE;
	m_camera.w = m_cameraBounds.w * WorldConstants::TILE_SIZE; //ensure camera size is always divisible by TILE_SIZE
	m_camera.h = m_cameraBounds.h * WorldConstants::TILE_SIZE;
}

BoundingBox Renderer::getCameraBounds() const
{
	return m_cameraBounds;
}

void Renderer::resetCamera()
{
	m_currentZoom = 1;
	m_camera.x = 0;
	m_camera.y = 0;
	m_camera.w = m_cameraSize.x;
	m_camera.h = m_cameraSize.y;
	m_cameraBounds.x = 0;
	m_cameraBounds.y = 0;
	m_cameraBounds.w = m_camera.w / WorldConstants::TILE_SIZE;
	m_cameraBounds.h = m_camera.h / WorldConstants::TILE_SIZE;
}

