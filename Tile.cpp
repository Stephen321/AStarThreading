#include "Tile.h"

Tile::Tile()
	: m_colour(255, 255, 5, 255)
	, m_rect({0,0,50,50})
{
}

void Tile::render(const Renderer& r) const
{
	r.drawRect(m_rect, m_colour);
}