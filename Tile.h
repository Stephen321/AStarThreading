#ifndef TILE_H
#define TILE_H

#include "Drawable.h"

class Tile : public Drawable
{
public:
	Tile();
	void render(const Renderer& r) const override;

private:
	Colour m_colour;
	SDL_Rect m_rect;
};

#endif