#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "GameObject.h"
#include "Tile.h"
#include "HelperFunctions.h"
#include "ThreadPool.h"
#include "AStar.h"

class Character : public GameObject
{
public:
	Character(const Vector2f& pos, Type type = Type::NPC, Character* target = 0);
	Character();
	~Character();
	void move();
	Character* getTarget() const;
	SDL_mutex* getWaitingForPathLock() const;
	void setPos(const Vector2f& v);
	void setTilePath(std::vector<Tile*> tilePath);
	void clearTilePath();
	int remainingPathPoints() const;

private:
	bool getWaitingForPath();
	void setWaitingForPath(bool value);
	Character* m_target;
	SDL_mutex* m_waitingForPathLock;
	Vector2i m_lastTargetPos;
	const int Border = 2;
	std::vector<Tile*> m_tilePath;
	bool m_waitingForPath;
};

#endif