#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "GameObject.h"

class Character : public GameObject
{
public:
	Character(const SDL_Rect& rect, Type type = Type::NPC);
	void move();

private:
	const int Border = 2;
	std::vector<Vector2i> m_tilePath;
};

#endif