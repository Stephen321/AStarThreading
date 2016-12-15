#ifndef ASTAR_H
#define ASTAR_H
#include "TileMap.h"
#include "ThreadPool.h"
#include "Renderer.h"

class Character;
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
	static void render(Renderer& r);
	static void setTileMap(TileMap* _tileMap);
	static void FindPath(Character* character, const Vector2i& end);
	static std::function<void()> getJobFunction(Character* character, const Vector2i& end);
	static void popLastPoints(Character* character);
	static void reset();
	static void removePoints(Character* character);

private:
	static std::map<Character*, std::vector<SDL_Point>> pathPoints;
	static TileMap* tileMap;
	static float calculateHeuristic(const Tile * current, const Tile * goal);
};
#include "Character.h"

#endif 
