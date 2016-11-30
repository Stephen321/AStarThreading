#include "GameObject.h"

GameObject::GameObject(Type type, const SDL_Rect& rect)
	: m_type(type)
	, m_rect(rect)
{
	switch (m_type)
	{
	case Type::Normal:
		m_colour = Colour(240, 240, 240, 255);
		break;
	case Type::Wall:
		m_colour = Colour(0, 255, 0, 255);
		break;
	case Type::Player:
		m_colour = Colour(255, 0, 0, 255);
		break;
	default:
		break;
	}
}

void GameObject::render(const Renderer& r) const
{
	r.drawRect(m_rect, m_colour, Colour(0, 0, 0, 255));
}
