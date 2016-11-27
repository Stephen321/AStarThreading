#ifndef RENDERER_H
#define RENDERER_H
#include "Debug.h"
#include "BasicTypes.h"
#include "WorldConstants.h"
#include "Drawable.h"
#include <SDL.h>

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
	void drawRect(SDL_Rect r, const Colour& fillColour, const Colour& outlineColour = Colour()) const;
	void present();
	Vector2D getCameraPos() const;
	void moveCamera(int xDir, int yDir);

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Rect m_camera;
	float m_windowWidth;
	float m_windowHeight;

	SDL_Rect applyCameraTransformation(const SDL_Rect& r) const;

};

#endif