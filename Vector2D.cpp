#include <Vector2D.h>

using namespace muddygames;

Vector2D::Vector2D(float x, float y) : m_x(x), m_y(y)
{
}

float Vector2D::GetX()
{
	return m_x;
}

float Vector2D::GetY()
{
	return m_y;
}

void Vector2D::SetX(float x)
{
	m_x = x;
}

void Vector2D::SetY(float y)
{
	m_y = y;
}
