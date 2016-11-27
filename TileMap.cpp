#include "TileMap.h"

TileMap::TileMap() 
	: m_size(0)
{

}

void TileMap::reset(int size)
{
	m_size = size;
	cleanUpTiles();

	m_topLeft = Vector2f(0.f, 0.f);
	m_tiles = new Tile*[m_size * m_size];

	Vector2i coords;
	Colour c(240, 240, 240, 255);
	SDL_Rect r = { m_topLeft.x, m_topLeft.y, TILE_SIZE, TILE_SIZE };

	for (; coords.y < m_size; coords.y++)
	{
		for (; coords.x < m_size; coords.x++)
		{
			m_tiles[coords.x + (coords.y * m_size)] = new Tile(coords, c, r);
			r.x += TILE_SIZE;
		}
		coords.x = 0;
		r.x = m_topLeft.x;
		r.y += TILE_SIZE;
	}

	for (int i = 0; i < m_size * m_size; i++)
	{
		Vector2i coord = posToCoords(m_tiles[i]->getPos());
		std::cout << "Coords x: " << coord.x << " y: " << coord.y << std::endl;
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
	for (int i = 0; i < m_size * m_size; i++)
	{
		r.render(m_tiles[i]);
	}
}

Vector2f TileMap::coordsToPos(Vector2i coords) const
{
	Vector2f pos;

	coords.x *= TILE_SIZE;
	coords.y *= TILE_SIZE;

	pos.x = coords.x + m_topLeft.x;
	pos.y = coords.y + m_topLeft.y;

	return pos;
}

Vector2i TileMap::posToCoords(Vector2f pos) const
{
	Vector2i coords;

	pos.x -= m_topLeft.x;
	pos.y -= m_topLeft.y;

	coords.x = pos.x / TILE_SIZE;
	coords.y = pos.y / TILE_SIZE;

	return coords;
}