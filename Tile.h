#ifndef TILE_H
#define TILE_H

#include "Drawable.h"

class Tile : public Drawable
{
public:
	Tile(const Vector2i& coords, const Colour& colour, const SDL_Rect& rect);
	void render(const Renderer& r) const override;
	Vector2i getCoords() const;
	Vector2f getPos() const;

private:
	Colour m_colour;
	SDL_Rect m_rect;
	Vector2i m_coords;
	Vector2f m_pos;
};

#endif