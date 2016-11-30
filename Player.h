#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(const SDL_Rect& rect);

private:
	const int Border = 2;
};

#endif