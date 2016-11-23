#include <GameObject.h>

GameObject::GameObject()
{
	DEBUG_MSG("Character Constructor");
}

GameObject::~GameObject()
{
	DEBUG_MSG("Character Destructor");
}

int GameObject::GetX()
{
	return m_x;
}

void GameObject::SetX(int x)
{
	m_x = x;
}

int GameObject::GetY()
{
	return m_y;
}

void GameObject::SetY(int y)
{
	m_y = y;
}
