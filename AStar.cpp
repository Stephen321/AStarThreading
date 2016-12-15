#include "AStar.h"

TileMap* AStar::tileMap = 0;
std::map<Character*, std::vector<SDL_Point>> AStar::pathPoints = std::map<Character*, std::vector<SDL_Point>>();

float AStar::calculateHeuristic(const Tile * current, const Tile * goal)
{
	Vector2f v = goal->getPos();
	v.x -= current->getPos().x;
	v.y -= current->getPos().y;
	return v.magnitude();
}

void AStar::reset()
{
	pathPoints.clear();
}

void AStar::removePoints(Character* character)
{
	pathPoints.erase(character);
}

void AStar::render(Renderer & r)
{
	SDL_SetRenderDrawColor(r.getRenderer(), 0, 255, 0, 255);
	for (auto & v : pathPoints)
	{
		std::vector<SDL_Point> transformedPoints;
		for (SDL_Point& p : v.second)
		{
			transformedPoints.push_back(r.applyCameraTransformationPoint(p));
		}
		SDL_RenderDrawLines(r.getRenderer(), &transformedPoints[0], transformedPoints.size());
	}
}

void AStar::setTileMap(TileMap* _tileMap)
{
	tileMap = _tileMap;
}

std::function<void()> AStar::getJobFunction(Character* character, const Vector2i& end)
{
	return std::bind(&AStar::FindPath, character, end);
}

void AStar::popLastPoints(Character * character)
{
	pathPoints.at(character).pop_back();
}

void AStar::FindPath(Character* character, const Vector2i& end)
{
	Vector2i start = Helper::posToCoords(character->getPos());
	int startIndex = start.x + (start.y * tileMap->getLength());
	int endIndex = end.x + (end.y * tileMap->getLength());
	if (startIndex >= tileMap->getLength() * tileMap->getLength() || startIndex < 0 ||
		endIndex >= tileMap->getLength() * tileMap->getLength() || endIndex < 0)
		return;

	std::map<int, Tile::Data> map;

	map[startIndex].g = 0;
	map[startIndex].f = calculateHeuristic(tileMap->getTile(startIndex), tileMap->getTile(endIndex));

	std::vector<Tile*> path;

	bool pathFound = false;

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, TileCostComparer> pq;

	pq.push(std::pair<int, int>(startIndex, map[startIndex].f));

	int neighbourOffets[8] = { -1, 0, 1, 0, 0, -1, 0, 1 };

	while (pathFound == false && pq.empty() == false)
	{
		if (ThreadPool::getInstance().getCanWork() == false) //this a star takes a while on the large map so we need to exit early if we finished working
			return;
		int currentIndex = pq.top().first;
		pq.pop();
		map[currentIndex].closed = true;
		Tile* current = tileMap->getTile(currentIndex);
		Vector2i currentCoords = Helper::posToCoords(current->getPos());
		if (current == tileMap->getTile(endIndex))
		{
			std::vector<Tile*> fullPath;
			std::vector<SDL_Point> points;
			for (Tile::Data td = map[currentIndex]; current != tileMap->getTile(startIndex); current = td.previous)
			{
				currentCoords = Helper::posToCoords(current->getPos());
				points.push_back({ (int)current->getPos().x + (int)(WorldConstants::TILE_SIZE * 0.5f), (int)current->getPos().y + (int)(WorldConstants::TILE_SIZE * 0.5f) });
				int index = currentCoords.x + (currentCoords.y * tileMap->getLength());
				td = map[index];
				fullPath.push_back(tileMap->getTile(index));
			}
			pathPoints[character] = points;
			int halfSize = fullPath.size() * 0.5f;
			path = (halfSize >= WorldConstants::HALF_SIZE_PATH_SPLIT_MIN) ? std::vector<Tile*>(fullPath.begin() + halfSize, fullPath.end()) : fullPath; //split on big paths
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
			//if closed or x and y werent valid so neighbour is 0 or neighbour is a wall or neighbour is the previous of the current
			if (neighbour == 0 || neighbourData.closed || neighbour == map[currentIndex].previous || neighbour == neighbourData.previous || neighbour->getType() == Tile::Type::Wall)
			{
				if (neighbour == 0 && notCreated) //if it is null and this was the first time creating it then remove from the map
				{
					map.erase(neighbourIndex); 
				}
				continue; //continue to next neighbour
			}

			int tenative_gScore = map[currentIndex].g + WorldConstants::G_COST; //cost between current and neighbour which always the same as no diagonals unless neighbour was a wall 
			
			if (tenative_gScore <= neighbourData.g) //is this path a lower cost than what is currently stored in it
			{
				//better path so store costs and previous
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
	if (ThreadPool::getInstance().getCanWork() == false || character == 0)
		return;
	character->setTilePath(path);
}