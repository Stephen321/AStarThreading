#include "GameObject.h"

GameObject::GameObject(Type type, const SDL_Rect& rect)
	: m_type(type)
	, m_rect(rect)
{
	resetColour();
}

void GameObject::resetColour()
{
	int x = m_rect.x / WorldConstants::TILE_SIZE;
	int y = m_rect.y / WorldConstants::TILE_SIZE;
	switch (m_type)
	{
	case Type::Normal:
		if (x % 2)
		{
			if (y % 2 == 0)
			{
				m_colour = Colour(WorldConstants::NORMAL_COLOUR_ONE);
			}
			else
			{
				m_colour = Colour(WorldConstants::NORMAL_COLOUR_TWO);
			}
		}
		else
		{
			if (y % 2 == 0)
			{
				m_colour = Colour(WorldConstants::NORMAL_COLOUR_TWO);
			}
			else
			{
				m_colour = Colour(WorldConstants::NORMAL_COLOUR_ONE);
			}
		}
		break;
	case Type::Wall:
		m_colour = Colour(WorldConstants::WALL_COLOUR);
		break;
	case Type::Player:
		m_colour = Colour(WorldConstants::PLAYER_COLOUR);
		break;
	case Type::NPC:
		m_colour = Colour(WorldConstants::NPC_COLOUR);
		break;
	default:
		break;
	}
}

void GameObject::render(const Renderer& r) const
{
	r.drawRect(m_rect, m_colour);
}

Vector2f GameObject::getPos() const
{
	return Vector2f(m_rect.x, m_rect.y);
}

GameObject::Type GameObject::getType() const
{
	return m_type;
}

void GameObject::setColour(const Colour & c)
{
	m_colour = c;
}

