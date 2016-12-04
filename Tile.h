#ifndef TILE_H
#define TILE_H

#include "GameObject.h"

class Tile : public GameObject
{
public:
	int g;
	int f;
	bool open;
	bool closed;
	Tile* previous;

	Tile(Type type, const SDL_Rect& rect);
};

#endif