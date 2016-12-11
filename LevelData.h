#ifndef  LEVELDATA_H
#define LEVELDATA_H

class LevelData
{
public:
	LevelData(int charSpawnWidth, int length, int walls, int touchingWalls);
	int getCharSpawnWidth() const;
	int getLength() const;
	int getWalls() const;
	int getTouchingWalls() const;
private:
	int m_charSpawnWidth;
	int m_length;
	int m_walls;
	int m_touchingWalls;
};

#endif 
