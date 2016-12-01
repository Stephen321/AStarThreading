#include "TileMap.h"

TileMap::TileMap() 
	: m_size(0)
	, m_topLeftCoords(Vector2i(0, 0))
{

}

void TileMap::reset(int size)
{
	m_size = size;
	cleanUpTiles();

	m_tiles = new Tile*[m_size * m_size];
	Vector2i coords;
	SDL_Rect r = { m_topLeftCoords.x * TILE_SIZE, m_topLeftCoords.y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

	for (int y = 0; y < m_size; y++)
	{
		for (int x = 0; x < m_size; x++)
		{
			m_tiles[x + (y * m_size)] = new Tile(Tile::Type::Normal, r);
			r.x += TILE_SIZE;
		}
		r.x = m_topLeftCoords.x * TILE_SIZE;
		r.y += TILE_SIZE;
	}

}

void TileMap::cleanUpTiles()
{
	if (m_tiles != 0)
	{
		for (int i = 0; i < m_size * m_size; i++)
		{
			delete m_tiles[i];
		}
		delete m_tiles;
	}
}

void TileMap::render(const Renderer& r) const
{
	BoundingBox visibleBounds = r.getCameraBounds();
	visibleBounds.x -= m_topLeftCoords.x;
	visibleBounds.y -= m_topLeftCoords.y;
	if (visibleBounds.x < 0)
	{
		visibleBounds.w += visibleBounds.x;
		visibleBounds.x = 0;
	}
	if (visibleBounds.y < 0)
	{
		visibleBounds.h += visibleBounds.y;
		visibleBounds.y = 0;
	}

	visibleBounds.w = std::fminf(m_size - visibleBounds.x, visibleBounds.w);
	visibleBounds.h= std::fminf(m_size - visibleBounds.y, visibleBounds.h);

	//std::cout << "X: " << visibleBounds.x << " Y: " << visibleBounds.y << " W: " << (visibleBounds.x + visibleBounds.w) << " H: " << (visibleBounds.y + visibleBounds.h) << std::endl;

	for (int y = visibleBounds.y; y < visibleBounds.y + visibleBounds.h; y++)
	{
		for (int x = visibleBounds.x; x < visibleBounds.x + visibleBounds.w; x++)
		{
			int index = x + (y * m_size);
			r.render(m_tiles[index]);
		}
	}
}

Vector2f TileMap::coordsToPos(Vector2i coords) const
{
	Vector2f pos;

	pos.x = (coords.x + m_topLeftCoords.x) * TILE_SIZE;
	pos.y = (coords.y + m_topLeftCoords.y) * TILE_SIZE;

	return pos;
}

Vector2i TileMap::posToCoords(Vector2f pos) const
{
	Vector2i coords;

	coords.x = (pos.x / TILE_SIZE) - m_topLeftCoords.x;
	coords.y = (pos.y / TILE_SIZE) - m_topLeftCoords.y;

	return coords;
}

int TileMap::getSize() const
{
	return m_size;
}
