#ifndef TILEMAP_H
#define TILEMAP_H
#include <vector>
#include <queue>
#include <map>
#include <numeric>
#include "Tile.h"

class TileMap : public Drawable
{
public:
	TileMap();
	void reset(int size);
	void cleanUpTiles();
	void render(const Renderer& r) const override;
	Vector2f coordsToPos(const Vector2i& coords) const;
	Vector2i posToCoords(const Vector2f& pos) const;
	int getSize() const;

	std::vector<Vector2i> getPath(const Vector2i& start, const Vector2i& end);

private:
	Vector2i m_topLeftCoords;
	int m_size;
	Tile ** m_tiles;

	int calculateHeuristic(const Tile * current, const Tile * goal);

	struct TileData {
		int g = std::numeric_limits<int>::max();
		int f = std::numeric_limits<int>::max();
		bool open;
		bool closed;
		Tile* previous;
	};

	class TileCostComparer
	{
	public:
		bool operator()(const std::pair<int, int>& t1, const std::pair<int, int>& t2)
		{
			return (t1.second> t2.second);
		}
	};
};

#endif 
