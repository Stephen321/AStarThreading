#include "Character.h"

Character::Character(const Vector2f& pos, Type type)
	: GameObject(type, pos)
{
	m_rect.x += Border * 0.5f;
	m_rect.y += Border * 0.5f;
	m_rect.w -= Border;
	m_rect.h -= Border;
}

Character::Character()
	: GameObject(Type::NPC)
{
}

Character & Character::operator=(const Character & rhs)
{
	m_colour = rhs.getColour();
	m_rect = rhs.getRect();
	m_type = rhs.getType();
	return *this;
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

void Character::setTilePath(std::vector<Vector2i> tilePath)
{
	m_tilePath = tilePath;
}

int Character::remainingPathPoints() const
{
	return m_tilePath.size();
}
