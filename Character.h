#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "GameObject.h"

class Character : public GameObject
{
public:
	Character(const Vector2f& pos, Type type = Type::NPC);
	Character();
	void move();
	void setPos(const Vector2i& v); //todo, remove this
	void setTilePath(std::vector<Vector2i> tilePath);
	int remainingPathPoints() const;
	Character& Character::operator=(const Character & rhs); //copy assignment operator as Characer has a const and cant implicitly copy

private:
	const int Border = 2;
	std::vector<Vector2i> m_tilePath;
};

#endif