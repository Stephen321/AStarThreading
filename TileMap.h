#ifndef TILEMAP_H
#define TILEMAP_H
#include <vector>
#include <queue>
#include <map>
#include <numeric>
#include "Tile.h"
#include "HelperFunctions.h"

class TileMap : public Drawable
{
public:
	enum Size
	{
		SMALL = 0,
		MEDIUM,
		LARGE

	};
	TileMap();
	void reset(Size size);
	void cleanUpTiles();
	void render(const Renderer& r) const override;
	Size getSize() const;
	int getLength() const;
	Tile::Type getTypeAt(const Vector2i& coords) const;
	Tile* getTile(int index) const;
	Tile* getTile(int x, int y) const;
	Tile* getTile(const Vector2i& coords) const;

private:
	struct Wall {
		Vector2i start;
		Vector2i end;
	};

	Size m_size;
	int m_length;
	Tile ** m_tiles;

	bool checkIfWall(const Wall& wall, const Vector2i& current);
	std::vector<Wall> createWalls();
};
#endif 
