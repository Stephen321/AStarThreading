#include "Tile.h"

Tile::Tile(Type type, const SDL_Rect& rect)
	: GameObject(type, rect)
{

}

Vector2f Tile::getPos() const
{
	return Vector2f(m_rect.x, m_rect.y);
}
