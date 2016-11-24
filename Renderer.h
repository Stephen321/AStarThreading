#ifndef RENDERER_H
#define RENDERER_H
#include "Debug.h"
#include <SDL.h>

using namespace std;

class Renderer 
{
public:
	Renderer();
	void cleanUp();
	void setDrawColor(int r, int g, int b, int a);
	void initialize();
	void clear();
	void present();
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

};
#endif // ! RENDERER_H
