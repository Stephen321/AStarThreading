#include "AStar.h"

TileMap* AStar::tileMap = 0;

float AStar::calculateHeuristic(const Tile * current, const Tile * goal)
{
	Vector2f v = goal->getPos();
	v.x -= current->getPos().x;
	v.y -= current->getPos().y;
	return v.magnitude();
}

void AStar::setTileMap(TileMap* _tileMap)
{
	tileMap = _tileMap;
}

void AStar::setCharacterPath(Character* character, const Vector2i& start, const Vector2i& end)
{
	int startIndex = start.x + (start.y * tileMap->getLength());
	int endIndex = end.x + (end.y * tileMap->getLength());

	std::map<int, Tile::Data> map;

	map[startIndex].g = 0;
	map[startIndex].f = calculateHeuristic(tileMap->getTile(startIndex), tileMap->getTile(endIndex));

	std::vector<Tile*> path;

	bool pathFound = false;
	if (tileMap->getTile(startIndex)->getType() == Tile::Type::Wall || tileMap->getTile(endIndex)->getType() == Tile::Type::Wall)
		pathFound = true;

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, TileCostComparer> pq;

	pq.push(std::pair<int, int>(startIndex, map[startIndex].f));

	int neighbourOffets[8] = { -1, 0, 1, 0, 0, -1, 0, 1 };

	//TODO: pointer to TileData which is in the map could be stored in pq instead?

	while (pathFound == false)
	{
		while (pq.empty() == false)
		{
			int currentIndex = pq.top().first;
			pq.pop();
			map[currentIndex].closed = true;
			Tile* current = tileMap->getTile(currentIndex);
			Vector2i currentCoords = Helper::posToCoords(current->getPos());
			if (current == tileMap->getTile(endIndex))
			{
				for (Tile::Data td = map[currentIndex]; current != tileMap->getTile(startIndex); current = td.previous)
				{
					//TODO: better way to do the path creation
					currentCoords = Helper::posToCoords(current->getPos());
					int index = currentCoords.x + (currentCoords.y * tileMap->getLength());
					td = map[index];
					path.push_back(tileMap->getTile(index));
				}
				pathFound = true;
			}

			for (int i = 0; i < 8; i += 2) //for each neighbour of current
			{
				int x = (currentCoords.x + neighbourOffets[i] >= 0 && currentCoords.x + neighbourOffets[i] < tileMap->getLength()) ? currentCoords.x + neighbourOffets[i] : -1;
				int y = (currentCoords.y + neighbourOffets[i + 1] >= 0 && currentCoords.y + neighbourOffets[i + 1] < tileMap->getLength()) ? currentCoords.y + neighbourOffets[i + 1] : -1;
				int neighbourIndex = x + (y * tileMap->getLength());
				Tile* neighbour = (x == -1 || y == -1) ? 0 : tileMap->getTile(neighbourIndex);
				bool notCreated = (map.find(neighbourIndex) == map.end());
				Tile::Data& neighbourData = map[neighbourIndex];

				if (neighbour == 0 || neighbourData.closed || neighbour == map[currentIndex].previous || neighbour == neighbourData.previous || neighbour->getType() == Tile::Type::Wall)
				{
					if (neighbour == 0 && notCreated) //invalid tiles
					{
						map.erase(neighbourIndex); //problem with this deleting existing if current neighbour invalid
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
					neighbourData.f = neighbourData.g + calculateHeuristic(neighbour, tileMap->getTile(endIndex));
				}
				if (neighbourData.open == false)
				{
					neighbourData.open = true;
					pq.push(std::pair<int, int>(neighbourIndex, neighbourData.f)); //we havnt fully evaluated this tile yet so push it
				}
			}
		}
	}
	
	character->setTilePath(path);
}