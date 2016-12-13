#ifndef TILE_H
#define TILE_H

#include "GameObject.h"

class Tile : public GameObject
{
public:
	struct Data {
		int g = std::numeric_limits<int>::max();
		int f = std::numeric_limits<int>::max();
		bool open;
		bool closed;
		Tile* previous;
	};
	Tile(Type type, const Vector2f& rect);
};

#endif