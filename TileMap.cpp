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

	Vector2i walls[30] = {
		Vector2i(10,5),
		Vector2i(10,6),
		Vector2i(10,7),
		Vector2i(10,8),
		Vector2i(10,9),
		Vector2i(10,10),
		Vector2i(10,11),
		Vector2i(10,12),
		Vector2i(10,13),
		Vector2i(10,14),
		Vector2i(11,5),
		Vector2i(12,5),
		Vector2i(13,5),
		Vector2i(14,5),
		Vector2i(15,5),
		Vector2i(25,15),
		Vector2i(25,16),
		Vector2i(25,17),
		Vector2i(25,18),
		Vector2i(25,19),
		Vector2i(25,20),
		Vector2i(20,21),
		Vector2i(20,22),
		Vector2i(20,23),
		Vector2i(10,24),
		Vector2i(11,24),
		Vector2i(12,24),
		Vector2i(13,24),
		Vector2i(14,24),
		Vector2i(15,24)
	};


	for (int y = 0; y < m_size; y++)
	{
		for (int x = 0; x < m_size; x++)
		{
			bool wall = false;
			for (Vector2i v : walls)
			{
				if (v.y == y && v.x == x)
				{
					wall = true;
				}
			}

			Tile::Type type = Tile::Type::Normal;
			if (wall)
			{
				type = Tile::Type::Wall;
			}
			m_tiles[x + (y * m_size)] = new Tile(type, r);
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

Vector2f TileMap::coordsToPos(const Vector2i& coords) const
{
	Vector2f pos;

	pos.x = (coords.x + m_topLeftCoords.x) * TILE_SIZE;
	pos.y = (coords.y + m_topLeftCoords.y) * TILE_SIZE;

	return pos;
}

Vector2i TileMap::posToCoords(const Vector2f& pos) const
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
	for (int i = 0; i < m_size * m_size; i++)
	{
		int x1 = posToCoords(m_tiles[i]->getPos()).x;
		int y1 = posToCoords(m_tiles[i]->getPos()).y;
		if (m_tiles[i]->getType() == Tile::Type::Wall)
		{
			continue;
		}
		if (x1 % 2)
		{
			if (y1 % 2 == 0)
			{
				m_tiles[i]->setColour(Colour(200, 200, 200, 255));
			}
			else
			{
				m_tiles[i]->setColour(Colour(70, 0, 160, 255));
			}
		}
		else
		{
			if (y1 % 2 == 0)
			{
				m_tiles[i]->setColour(Colour(70, 0, 160, 255));
			}
			else
			{
				m_tiles[i]->setColour(Colour(200, 200, 200, 255));
			}
		}
		//m_tiles[i]->m_colour = Colour(240, 240, 240, 255); //TODO: remove this
	}

	int startIndex = start.x + (start.y * m_size);
	int endIndex = end.x + (end.y * m_size);


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
		Vector2i currentCoords = posToCoords(current->getPos());
		if (current == m_tiles[endIndex])
		{
			for (TileData td = map[currentIndex]; current != m_tiles[startIndex]; current = td.previous)
			{
				current->setColour(Colour(0, 255, 0, 255));
				//TODO: better way to do the path creation
				currentCoords = posToCoords(current->getPos());
				int index = currentCoords.x + (currentCoords.y * m_size);
				td = map[index];
			}
			return  path;
		}
		pq.pop();
		map[currentIndex].closed = true;

		for (int i = 0; i < 8; i += 2) //for each neighbour of current
		{
			int x = (currentCoords.x + neighbourOffets[i] >= 0 && currentCoords.x + neighbourOffets[i] < m_size) ? currentCoords.x + neighbourOffets[i] : -1;
			int y = (currentCoords.y + neighbourOffets[i + 1] >= 0 && currentCoords.y + neighbourOffets[i + 1] < m_size) ? currentCoords.y + neighbourOffets[i + 1] : -1;
			int neighbourIndex = x + (y * m_size);
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
