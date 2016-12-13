#include "TileMap.h"

TileMap::TileMap() 
	: m_length(0)
{

}

void TileMap::reset(Size size)
{
	//*clean up any tiles from previous levels first before changing size/length*
	cleanUpTiles();

	//set up level data
	m_size = size;
	const LevelData levelData = WorldConstants::levels[m_size];
	m_length = levelData.getLength();

	//create new tiles
	m_tiles = new Tile*[m_length * m_length];

	Vector2f pos;

	//create random walls for the current sized level
	std::vector<Wall> walls = createWalls();

	for (int y = 0; y < m_length; y++)
	{
		for (int x = 0; x < m_length; x++)
		{
			bool isWall = false;
			for (Wall wall : walls) //loops through walls to check if the current tile is one
			{
				if (checkIfWall(wall, Vector2i(x, y)))
				{
					isWall = true;
					break;
				}
			}

			Tile::Type type = Tile::Type::Normal;
			if (isWall)
			{
				type = Tile::Type::Wall;
			}
			m_tiles[x + (y * m_length)] = new Tile(type, pos);
			pos.x += WorldConstants::TILE_SIZE;
		}
		pos.x = 0;
		pos.y += WorldConstants::TILE_SIZE;
	}
}		


std::vector<TileMap::Wall> TileMap::createWalls()
{
	std::vector<Wall> walls;
	const LevelData levelData = WorldConstants::levels[m_size];

	int tileHeight = m_length - 1;
	int wallCount = levelData.getWalls();
	int touchingCount = levelData.getTouchingWalls();
	int maxDist = (tileHeight - (levelData.getCharSpawnWidth() * 2)) / wallCount;
	int lastOffset = levelData.getCharSpawnWidth();

	for (int i = 0; i < wallCount; i++)
	{
		int offset;
		if (i == 0)
		{
			offset = Helper::random(levelData.getCharSpawnWidth(), levelData.getCharSpawnWidth() + (maxDist * (i + 1)));
		}
		else
		{
			offset = Helper::random(lastOffset + WorldConstants::MIN_WALL_DISTANCE + 1, levelData.getCharSpawnWidth() + (maxDist * (i + 1)));
		}
		lastOffset = offset; 

		int startY = Helper::random(WorldConstants::MIN_WALL_EDGE_GAP, WorldConstants::MAX_WALL_EDGE_GAP);
		int endY = tileHeight - Helper::random(WorldConstants::MIN_WALL_EDGE_GAP, WorldConstants::MAX_WALL_EDGE_GAP);
		if (touchingCount > 0 && rand() % 2 == 0)
		{
			if (rand() % 2 == 0)
			{
				startY = 0;
			}
			else
			{
				endY = tileHeight;
			}
			touchingCount--;
		}
		Wall w;
		w.start = Vector2i(offset, startY);
		w.end = Vector2i(offset, endY);

		walls.push_back(w);
	}

	return walls;
}

bool TileMap::checkIfWall(const Wall& wall, const Vector2i& current)
{
	bool isWall = false;

	if (wall.start.x == current.x)
	{
		if (current.y >= wall.start.y && current.y <= wall.end.y)
		{
			isWall = true;
		}
	}
	//else if (wall.start.y == current.y) //horizontal walls
	//{
	//	if (current.x >= wall.start.x && current.x <= wall.end.x)
	//	{
	//		isWall = true;
	//	}
	//}

	return isWall;
}

void TileMap::cleanUpTiles()
{
	if (m_tiles != 0)
	{
		for (int i = 0; i < m_length * m_length; i++)
		{
			delete m_tiles[i]; // TODO: check if no threads using tiles??
		}
		delete m_tiles;
	}
}

void TileMap::render(const Renderer& r) const
{
	BoundingBox visibleBounds = r.getCameraBounds();
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

	visibleBounds.w = std::fminf(m_length - visibleBounds.x, visibleBounds.w);
	visibleBounds.h= std::fminf(m_length - visibleBounds.y, visibleBounds.h);

	//std::cout << "X: " << visibleBounds.x << " Y: " << visibleBounds.y << " W: " << (visibleBounds.x + visibleBounds.w) << " H: " << (visibleBounds.y + visibleBounds.h) << std::endl;

	for (int y = visibleBounds.y; y < visibleBounds.y + visibleBounds.h; y++)
	{
		for (int x = visibleBounds.x; x < visibleBounds.x + visibleBounds.w; x++)
		{
			int index = x + (y * m_length);
			r.render(m_tiles[index]);
		}
	}
}

TileMap::Size TileMap::getSize() const
{
	return m_size;
}

int TileMap::getLength() const
{
	return m_length;
}

Tile* TileMap::getTile(int index) const
{
	return m_tiles[index];
}

Tile* TileMap::getTile(int x, int y) const
{
	return m_tiles[x + (y * m_length)];
}

Tile* TileMap::getTile(const Vector2i& coords) const
{
	return m_tiles[coords.x + (coords.y * m_length)];
}

Tile::Type TileMap::getTypeAt(const Vector2i& coords) const
{
	return m_tiles[coords.x + (coords.y * m_length)]->getType();
}
