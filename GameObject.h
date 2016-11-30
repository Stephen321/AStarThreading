#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Drawable.h"

class GameObject : public Drawable
{
public:
	enum class Type {
		Normal,
		Wall,
		Player,
		AI
	};
	GameObject(Type type, const SDL_Rect& rect);
	virtual void render(const Renderer& r) const override;
protected:
	Colour m_colour;
	SDL_Rect m_rect;
	Type m_type;
};

#endif
