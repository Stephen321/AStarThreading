#ifndef RENDERER_H
#define RENDERER_H
#include "Debug.h"
#include "BasicTypes.h"
#include "WorldConstants.h"
#include "Drawable.h"
#include <SDL.h>
#include "HelperFunctions.h"

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
	void drawRect(SDL_Rect r, const Colour& fillColour) const;
	void present();
	void moveCamera(int xDir, int yDir);
	void resetCamera();
	void zoom(int dir);
	BoundingBox getCameraBounds() const;
	SDL_Renderer* getRenderer();
	SDL_Point applyCameraTransformationPoint(SDL_Point& p);

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Rect m_camera;
	const float ZOOM_AMOUNT = 0.025f;
	float m_currentZoom;
	Vector2i m_cameraSize;

	float m_windowWidth;
	float m_windowHeight;
	BoundingBox m_cameraBounds;

	SDL_Rect applyCameraTransformation(const SDL_Rect& r) const;

};

#endif