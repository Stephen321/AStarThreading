#ifndef TILE_H
#define TILE_H

#include "GameObject.h"

class Tile : public GameObject
{
public:
	Tile(Type type, const SDL_Rect& rect);
};

#endif