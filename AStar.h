#ifndef ASTAR_H
#define ASTAR_H
#include "TileMap.h"
#include "Character.h"

//A Star
class AStar
{
public:
	class TileCostComparer
	{
	public:
		bool operator()(const std::pair<int, int>& t1, const std::pair<int, int>& t2)
		{
			return (t1.second> t2.second);
		}
	};
	static void setCharacterPath(const TileMap& tileMap, Character* character, const Vector2i& start, const Vector2i& end);

private:
	static float calculateHeuristic(const Tile * current, const Tile * goal);
};

#endif 
