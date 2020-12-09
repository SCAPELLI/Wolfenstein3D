#ifndef WOLFENSTEIN3D_SCREEN_H
#define WOLFENSTEIN3D_SCREEN_H
#include "Camera.h"
#include "SDL2/SDL.h"

class Screen{
	Camera* camera;
	int h, w;
	SDL_Window* window;
	SDL_Renderer* renderer;

	public:

		Screen(Camera* camera, int h, int w);
		void draw();
		~Screen();
};

#endif