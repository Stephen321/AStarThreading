#include "GameObject.h"

GameObject::GameObject(Type type, const SDL_Rect& rect)
	: m_type(type)
	, m_rect(rect)
{
	int x = m_rect.x / TILE_SIZE;
	int y = m_rect.y / TILE_SIZE;
	switch (m_type)
	{
	case Type::Normal:
		if (x % 2)
		{
			if (y % 2 == 0)
			{
				m_colour = Colour(200, 200, 200, 255);
			}
			else
			{
				m_colour = Colour(70, 0, 160, 255);
			}
		}
		else
		{
			if (y % 2 == 0)
			{
				m_colour = Colour(70, 0, 160, 255);
			}
			else
			{
				m_colour = Colour(200, 200, 200, 255);
			}
		}
		m_colour = Colour(240, 240, 240, 255); //TODO: remove this
		break;
	case Type::Wall:
		m_colour = Colour(0, 0, 0, 255);
		break;
	case Type::Player:
		m_colour = Colour(255, 0, 0, 255);
		break;
	case Type::NPC:
		m_colour = Colour(0, 0, 255, 255);
		break;
	default:
		break;
	}
}

void GameObject::render(const Renderer& r) const
{
	r.drawRect(m_rect, m_colour, Colour(0, 0, 0, 255));
}

Vector2f GameObject::getPos() const
{
	return Vector2f(m_rect.x, m_rect.y);
}

GameObject::Type GameObject::getType() const
{
	return m_type;
}

