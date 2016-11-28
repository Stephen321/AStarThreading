#ifndef TILE_H
#define TILE_H

#include "Drawable.h"

class Tile : public Drawable
{
public:
	enum class Type {
		Normal,
		Wall
	};
	Tile(Type type, const SDL_Rect& rect);
	void render(const Renderer& r) const override;
	Vector2f getPos() const;

private:
	Colour m_colour;
	SDL_Rect m_rect;
	Type m_type;
};

#endif