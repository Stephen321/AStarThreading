#include "Character.h"

Character::Character(const Vector2f& pos, Type type, Character* target)
	: GameObject(type, pos)
	, m_target(target)
	, m_waitingForPath(false)
	, m_waitingForPathLock(SDL_CreateMutex())
{
}

Character::Character()
	: GameObject(Type::NPC)
{
}

Character::~Character()
{
	m_target = 0;
	SDL_DestroyMutex(m_waitingForPathLock);
	m_waitingForPathLock = NULL;
}

void Character::move()
{
	if (getWaitingForPath() == false)
	{
		if (m_tilePath.size() != 0)
		{
			setPos(m_tilePath.back()->getPos()); //get next target tile
			AStar::popLastPoints(this);
			m_tilePath.pop_back();
		}
		else if (m_target != 0 && m_lastTargetPos != Helper::posToCoords(m_target->getPos()))
		{
			m_lastTargetPos = Helper::posToCoords(m_target->getPos());
			if (USE_THREADS)
			{
				setWaitingForPath(true);
				ThreadPool::getInstance().addJob(AStar::getJobFunction(this, Helper::posToCoords(m_target->getPos())));
			}
			else
			{
				m_waitingForPath = false;
				AStar::FindPath(this, Helper::posToCoords(m_target->getPos()));
			}
		}
	}
}

Character * Character::getTarget() const
{
	return m_target;
}

SDL_mutex * Character::getWaitingForPathLock() const
{
	return m_waitingForPathLock;
}


bool Character::getWaitingForPath()
{
	bool b;
	SDL_LockMutex(m_waitingForPathLock);
	b = m_waitingForPath;
	SDL_UnlockMutex(m_waitingForPathLock);
	return b;
}

void Character::setWaitingForPath(bool value)
{
	SDL_LockMutex(m_waitingForPathLock);
	m_waitingForPath = value;
	SDL_UnlockMutex(m_waitingForPathLock);
}

void Character::setPos(const Vector2f& v)
{
	m_rect.x = v.x;
	m_rect.y = v.y;
}

void Character::setTilePath(std::vector<Tile*> tilePath) //called from threads after they do astar to get the path
{
	if (USE_THREADS)
	{
		setWaitingForPath(false);
		m_tilePath = tilePath;
	}
	else
	{
		m_tilePath = tilePath;
	}
}

void Character::clearTilePath()
{
	m_tilePath.clear();
}

int Character::remainingPathPoints() const
{
	return m_tilePath.size();
}
