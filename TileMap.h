#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

class TileMap : public Drawable
{
public:
	TileMap();
	void reset(int size);
	void cleanUpTiles();
	void render(const Renderer& r) const override;
	Vector2f coordsToPos(Vector2i coords) const;
	Vector2i posToCoords(Vector2f pos) const;
	int getSize() const;

private:
	Vector2i m_topLeftCoords;
	int m_size;
	Tile ** m_tiles;
};

#endif 
