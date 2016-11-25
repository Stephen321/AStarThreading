#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Renderer.h"

class Drawable
{
public:
	virtual void render(const Renderer& r) const = 0;
};
#endif