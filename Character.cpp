#include "Character.h"

Character::Character(const Vector2f& pos, Type type)
	: GameObject(type, pos)
	, m_elapsedTime(0)
{
	m_rect.x += Border * 0.5f;
	m_rect.y += Border * 0.5f;
	m_rect.w -= Border;
	m_rect.h -= Border;
	m_startPos = pos;
	m_targetPos = pos;
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
	m_startPos = rhs.getPos();
	m_targetPos = rhs.getPos();
	return *this;
}

void Character::move()
{
	if (m_tilePath.size() != 0)
	{
		//TODO: use directions rather than absolute path for smooth motion between tiles?
		m_startPos = getPos();
		m_targetPos = m_tilePath.back()->getPos(); //get next target tile
		m_tilePath.pop_back();
		m_elapsedTime = 0;
	}
}

void Character::update(int dt)
{
	setPos(Helper::lerp((float)m_elapsedTime / WorldConstants::TICKS_PER_CHAR_UPDATE, m_startPos, m_targetPos));
	m_elapsedTime += dt;
}

void Character::setPos(const Vector2f& v)
{
	m_rect.x = v.x + (Border * 0.5f);
	m_rect.y = v.y + (Border * 0.5f);
}

void Character::setPos(const Vector2i& v)
{
	m_rect.x = v.x * WorldConstants::TILE_SIZE;
	m_rect.y = v.y * WorldConstants::TILE_SIZE;
}

void Character::setTilePath(std::vector<Tile*> tilePath)
{
	m_tilePath = tilePath;
	m_startPos = m_tilePath.back()->getPos();
	m_targetPos = m_tilePath.back()->getPos();
}

int Character::remainingPathPoints() const
{
	return m_tilePath.size();
}
