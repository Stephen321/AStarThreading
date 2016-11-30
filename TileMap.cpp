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
	SDL_Rect r = { m_topLeft.x, m_topLeft.y, TILE_SIZE, TILE_SIZE };

	for (int y = 0; y < m_size; y++)
	{
		for (int x = 0; x < m_size; x++)
		{
			m_tiles[x + (y * m_size)] = new Tile(Tile::Type::Normal, r);
			r.x += TILE_SIZE;
		}
		r.x = m_topLeft.x;
		r.y += TILE_SIZE;
	}

	//for (int i = 0; i < m_size * m_size; i++)
	//{
		//Vector2i coord = posToCoords(m_tiles[i]->getPos());
		//std::cout << "Coords x: " << coord.x << " y: " << coord.y << std::endl;
	//}

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

	BoundingBox cameraBounds = r.getCameraBounds();
	if (cameraBounds.x < 0)
	{
		cameraBounds.x = 0;
	}
	if (cameraBounds.y < 0)
	{
		cameraBounds.y = 0;
	}
	//TODO: this always draws the full camera width of tiles even if they are off the right or bottom side of the screen
	//TODO: also it doesnt work
	if (m_size < cameraBounds.w)
	{
		cameraBounds.w = m_size - cameraBounds.x;
	}
	if (m_size < cameraBounds.h)
	{
		cameraBounds.h = m_size - cameraBounds.y;
	}
	for (int y = cameraBounds.x; y < cameraBounds.y + cameraBounds.h; y++)
	{
		for (int x = cameraBounds.y; x < cameraBounds.x + cameraBounds.w; x++)
		{
			int index = x + (y * m_size);
			r.render(m_tiles[index]);
		}
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

int TileMap::getSize() const
{
	return m_size;
}
