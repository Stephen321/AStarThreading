#include "Tile.h"

Tile::Tile(Type type, const SDL_Rect& rect)
	: m_type(type)
	, m_rect(rect)
{
	switch (m_type)
	{
	case Type::Normal:
		m_colour = Colour(240, 240, 240, 255);
		break;
	case Type::Wall:
		m_colour = Colour(0, 255, 0, 255);
		break;
	default:
		break;
	}
}

void Tile::render(const Renderer& r) const
{
	r.drawRect(m_rect, m_colour, Colour(0, 0, 0, 255));
}

Vector2f Tile::getPos() const
{
	return Vector2f(m_rect.x, m_rect.y);
}
