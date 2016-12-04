#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Drawable.h"

class GameObject : public Drawable
{
public:

	//TODO: cut this down 
	enum class Type : Uint8 {
		Normal,
		Wall,
		NPC,
		Player
	};
	GameObject(Type type, const SDL_Rect& rect);
	virtual void render(const Renderer& r) const override;
	Vector2f getPos() const;
	Type getType() const;
	void setColour(const Colour& c);

protected:
	Colour m_colour;
	SDL_Rect m_rect;
	Type m_type;
};

#endif
