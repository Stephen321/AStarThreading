#include "TileMap.h"

TileMap::TileMap() 
	: m_length(0)
{

}

void TileMap::reset(Size size)
{
	//set up level data
	m_size = size;
	const LevelData levelData = WorldConstants::levels[m_size];
	m_length = levelData.getLength();

	//clean up any tiles from previous levels
	cleanUpTiles();

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
	int maxDist = (tileHeight - (levelData.getCharSpawnWidth() * 2)) / (wallCount - 1);
	int minDist = WorldConstants::MIN_WALL_DISTANCE;

	for (int i = 0; i < wallCount; i++)
	{
		int offset = levelData.getCharSpawnWidth() + (maxDist * i); //TODO: need random walls (use minDist)
		
		//between rand min and max
		
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
		else
		{
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
			delete m_tiles[i];
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

int TileMap::calculateHeuristic(const Tile * current, const Tile * goal)
{
	Vector2f v = goal->getPos();
	v.x -= current->getPos().x;
	v.y -= current->getPos().y;
	return v.magnitude();
}

std::vector<Vector2i> TileMap::getPath(const Vector2i& start, const Vector2i& end)
{
	//reset all
	for (int i = 0; i < m_length * m_length; i++)
	{
		int x1 = Helper::posToCoords(m_tiles[i]->getPos()).x;
		int y1 = Helper::posToCoords(m_tiles[i]->getPos()).y;
		m_tiles[i]->resetColour();
	}

	int startIndex = start.x + (start.y * m_length);
	int endIndex = end.x + (end.y * m_length);


	std::map<int, TileData> map;

	map[startIndex].g = 0;
	map[startIndex].f = calculateHeuristic(m_tiles[startIndex], m_tiles[endIndex]);

	std::vector<Vector2i> path;

	if (m_tiles[startIndex]->getType() == Tile::Type::Wall || m_tiles[endIndex]->getType() == Tile::Type::Wall)
		return path;

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int,int>>, TileCostComparer> pq;

	pq.push(std::pair<int, int>(startIndex, map[startIndex].f));

	int neighbourOffets[8] = { -1, 0, 1, 0, 0, -1, 0, 1 };

	//TODO: pointer to TileData which is in the map could be stored in pq instead?

	while (pq.empty() == false)
	{
		int currentIndex = pq.top().first;
		Tile* current = m_tiles[currentIndex];
		Vector2i currentCoords = Helper::posToCoords(current->getPos());
		if (current == m_tiles[endIndex])
		{
			for (TileData td = map[currentIndex]; current != m_tiles[startIndex]; current = td.previous)
			{
				current->setColour(Colour(0, 255, 0, 255));
				//TODO: better way to do the path creation
				currentCoords = Helper::posToCoords(current->getPos());
				int index = currentCoords.x + (currentCoords.y * m_length);
				td = map[index];
				path.push_back(currentCoords);
			}
			return  path;
		}
		pq.pop();
		map[currentIndex].closed = true;

		for (int i = 0; i < 8; i += 2) //for each neighbour of current
		{
			int x = (currentCoords.x + neighbourOffets[i] >= 0 && currentCoords.x + neighbourOffets[i] < m_length) ? currentCoords.x + neighbourOffets[i] : -1;
			int y = (currentCoords.y + neighbourOffets[i + 1] >= 0 && currentCoords.y + neighbourOffets[i + 1] < m_length) ? currentCoords.y + neighbourOffets[i + 1] : -1;
			int neighbourIndex = x + (y * m_length);
			Tile* neighbour = (x == -1 || y  == -1) ? 0 : m_tiles[neighbourIndex];
			TileData& neighbourData = map[neighbourIndex];

			if (neighbour == 0 || neighbourData.closed || neighbour == neighbourData.previous || neighbour->getType() == Tile::Type::Wall)
			{
				if (neighbour == 0) //invalid tiles
				{
					map.erase(neighbourIndex);
				}
				continue; //continue to next neighbour
			}

			int tenative_gScore = map[currentIndex].g + 10; //10 is cost between current and neighbour which always the same as no diagonals unless neighbour was a wall 
			if (neighbourIndex == 868)
			{
				int test = 0;
			}
			if (tenative_gScore <= neighbourData.g)
			{
				//better path
				neighbourData.previous = current;
				neighbourData.g = tenative_gScore;
				neighbourData.f = neighbourData.g + calculateHeuristic(neighbour, m_tiles[endIndex]);
			}
			if (neighbourData.open == false)
			{
				neighbourData.open = true;
				neighbour->setColour(Colour(175, 238, 238, 255));
				pq.push(std::pair<int, int>(neighbourIndex, neighbourData.f)); //we havnt fully evaluated this tile yet so push it
			}
		}
	}

	return  path;
}

Tile::Type TileMap::getTypeAt(const Vector2i & coords)
{
	return m_tiles[coords.x + (coords.y * m_size)]->getType();
}
