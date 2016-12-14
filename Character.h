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
	void update(int dt);
	void move();
	Character* getTarget() const;
	void setPos(const Vector2f& v);
	void setPos(const Vector2i& v); //todo, remove this
	void setTilePath(std::vector<Tile*> tilePath);
	int remainingPathPoints() const;
	Character& Character::operator=(const Character & rhs); //copy assignment operator as Characer has a const and cant implicitly copy

private:
	Character* m_target;
	Vector2i m_lastTargetPos;
	const int Border = 2;
	std::vector<Tile*> m_tilePath;
	float m_elapsedTime;
	Vector2f m_targetPos;
	Vector2f m_startPos;
	bool m_waitingForPath;

};

#endif