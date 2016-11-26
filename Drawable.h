#ifndef DRAWABLE_H
#define DRAWABLE_H


class Renderer; //TODO: remove this
class Drawable
{
public:
	virtual void render(const Renderer& r) const = 0;
};
#include "Renderer.h"

#endif