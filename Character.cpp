#include "Character.h"

Character::Character(const SDL_Rect& rect, Type type)
	: GameObject(type, rect)
{
	m_rect.x += Border * 0.5f;
	m_rect.y += Border * 0.5f;
	m_rect.w -= Border;
	m_rect.h -= Border;
}

void Character::move()
{
	if (m_tilePath.size() != 0)
	{
		//TODO: use directions rather than absolute path for smooth motion between tiles?
		Vector2i target = m_tilePath.back(); //get next target tile
		m_tilePath.pop_back();
		m_rect.x = (Border * 0.5f) + (target.x * WorldConstants::TILE_SIZE);
		m_rect.y = (Border * 0.5f) + (target.y * WorldConstants::TILE_SIZE);
	}
}


void Character::setPos(const Vector2i& v)
{
	m_rect.x = v.x * WorldConstants::TILE_SIZE;
	m_rect.y = v.y * WorldConstants::TILE_SIZE;
}
