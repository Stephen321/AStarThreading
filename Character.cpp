#include "Character.h"

Character::Character(const Vector2f& pos, Type type, Character* target)
	: GameObject(type, pos)
	, m_target(target)
	, m_elapsedTime(0)
	, m_waitingForPath(false)
{
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
	m_target = rhs.getTarget();
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
	else if (m_waitingForPath == false && m_target != 0 && m_lastTargetPos != Helper::posToCoords(m_target->getPos()))
	{
		m_lastTargetPos = Helper::posToCoords(m_target->getPos());
		m_waitingForPath = true;
		std::cout << "adding job" << std::endl;
		ThreadPool::getInstance().addJob(AStar::getJobFunction(this, Helper::posToCoords(m_target->getPos())));
	}
}

Character * Character::getTarget() const
{
	return m_target;
}

void Character::update(int dt)
{
	setPos(Helper::lerp((float)m_elapsedTime / WorldConstants::TICKS_PER_CHAR_UPDATE, m_startPos, m_targetPos));
	m_elapsedTime += dt;
}

void Character::setPos(const Vector2f& v)
{
	m_rect.x = v.x;
	m_rect.y = v.y;
}

void Character::setPos(const Vector2i& v)
{
	m_rect.x = v.x * WorldConstants::TILE_SIZE;
	m_rect.y = v.y * WorldConstants::TILE_SIZE;
}

void Character::setTilePath(std::vector<Tile*> tilePath)
{
	m_waitingForPath = false;
	m_elapsedTime = 0.f;
	m_tilePath = tilePath;
}

int Character::remainingPathPoints() const
{
	return m_tilePath.size();
}
