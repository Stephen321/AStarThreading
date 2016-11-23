#include <GameObjectParameters.h>

GameObjectParameters::GameObjectParameters() : m_x(0), m_y(0)
{
	DEBUG_MSG("Default GameObjectParameters Constructor");
}

GameObjectParameters::GameObjectParameters(int x, int y) : m_x (x), m_y(y)
{
	DEBUG_MSG("Arguments based GameObjectParameters Constructor");
}

GameObjectParameters::~GameObjectParameters()
{
	DEBUG_MSG("GameObjectParameters Destructor");
}

int GameObjectParameters::GetX() const
{
	return m_x;
}

int GameObjectParameters::GetY() const
{
	return m_y;
}

