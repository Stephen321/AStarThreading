#include "Tile.h"

Tile::Tile(int x, int y, const Colour& colour, const SDL_Rect& rect)
	: m_x(x)
	, m_y(y)
	, m_colour(colour)
	, m_rect(rect)
{
}

void Tile::render(const Renderer& r) const
{
	r.drawRect(m_rect, m_colour, Colour(0, 0, 0, 255));
}