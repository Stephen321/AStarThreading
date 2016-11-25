#ifndef RENDERER_H
#define RENDERER_H
#include "Debug.h"
#include "BasicTypes.h"
#include <SDL.h>

class Drawable; //TODO: remove this
class Renderer 
{
public:
	Renderer();
	void cleanUp();
	void setDrawColour(int r, int g, int b, int a) const;
	void setDrawColour(const Colour& c) const;
	bool initialize(const char* title, int width, int height, int flags);
	void clear();
	void render(const Drawable* d) const;
	void drawRect(const SDL_Rect& r, const Colour& fillColour, const Colour& outlineColour = Colour()) const;
	void present();
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

};

#include "Drawable.h"

#endif