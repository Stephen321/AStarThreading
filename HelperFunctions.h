#ifndef  HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <random>
#include "BasicTypes.h"
#include "WorldConstants.h"

namespace Helper
{

	inline Vector2f coordsToPos(const Vector2i& coords)
	{
		return Vector2f(coords.x * WorldConstants::TILE_SIZE, coords.y * WorldConstants::TILE_SIZE);
	}

	inline Vector2i posToCoords(const Vector2f& pos)
	{
		return Vector2i(pos.x / WorldConstants::TILE_SIZE, pos.y / WorldConstants::TILE_SIZE);
	}

	inline int random(int min, int max)
	{
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(min, max);
		return (distr(eng));
	}
	inline int clamp(int value, int min, int max)
	{
		if (value < min)
			value = min;
		else if (value >= max)
			value = max - 1;
		return value;
	}

	inline Vector2f lerp(float t, Vector2f a, Vector2f b) 
	{
		if (t > 1.f)
			t = 1.f;
		return a*(1 - t) + b*t;
	}
}
#endif 
