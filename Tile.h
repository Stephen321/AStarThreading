#ifndef TILE_H
#define TILE_H

#include "Drawable.h"

class Tile : public Drawable
{
public:
	Tile(int x, int y, const Colour& colour, const SDL_Rect& rect);
	void render(const Renderer& r) const override;

private:
	Colour m_colour;
	SDL_Rect m_rect;
	int m_x;
	int m_y;
};

#endif