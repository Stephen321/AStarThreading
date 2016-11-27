#include "Tile.h"

Tile::Tile(const Vector2i& coords, const Colour& colour, const SDL_Rect& rect)
	: m_coords(coords)
	, m_colour(colour)
	, m_rect(rect)
	, m_pos(m_rect.x, m_rect.y)
{
}

void Tile::render(const Renderer& r) const
{
	r.drawRect(m_rect, m_colour, Colour(0, 0, 0, 255));
}

Vector2i Tile::getCoords() const
{
	return m_coords;
}

Vector2f Tile::getPos() const
{
	return m_pos;
}
