#ifndef TILE_H
#define TILE_H

#include "GameObject.h"

class Tile : public GameObject
{
public:
	Tile(Type type, const Vector2f& rect);
};

#endif