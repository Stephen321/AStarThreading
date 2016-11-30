#include "Player.h"

Player::Player(const SDL_Rect& rect)
	: GameObject(Type::Player, rect)
{
	m_rect.x += Border * 0.5f;
	m_rect.y += Border * 0.5f;
	m_rect.w -= Border;
	m_rect.h -= Border;
}