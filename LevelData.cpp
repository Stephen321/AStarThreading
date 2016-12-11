#include "LevelData.h"

LevelData::LevelData(int charSpawnWidth, int npcCount, int length, int wallsCount, int touchingWalls)
	: m_charSpawnWidth(charSpawnWidth)
	, m_npcCount(npcCount)
	, m_length(length)
	, m_walls(wallsCount)
	, m_touchingWalls(touchingWalls)
{
}

int LevelData::getCharSpawnWidth() const
{
	return m_charSpawnWidth;
}

int LevelData::getNpcCount() const
{
	return m_npcCount;
}

int LevelData::getLength() const
{
	return m_length;
}

int LevelData::getWalls() const
{
	return m_walls;
}

int LevelData::getTouchingWalls() const
{
	return m_touchingWalls;
}