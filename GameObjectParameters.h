#ifndef GAME_OBJECT_PARAMETERS_H
#define GAME_OBJECT_PARAMETERS_H

#include <iostream>
#include "Debug.h"

using namespace std;

class GameObjectParameters
{
public:
	GameObjectParameters(int, int);
	int GetX() const;
	int GetY() const;
protected:
	GameObjectParameters();
	virtual ~GameObjectParameters();
private:
	int m_x;
	int m_y;
};
#endif
