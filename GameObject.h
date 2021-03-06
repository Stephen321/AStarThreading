#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Drawable.h"

class GameObject : public Drawable
{
public:

	enum class Type : Uint8 {
		Normal,
		Wall,
		NPC,
		Player
	};
	GameObject(Type type, const Vector2f& pos = Vector2f());
	virtual void render(const Renderer& r) const override;
	Vector2f getPos() const;
	Type getType() const;
	void setColour(const Colour& c);
	void resetColour();

protected:
	Colour m_colour;
	SDL_Rect m_rect;
	Type m_type;
};

#endif
