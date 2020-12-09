#ifndef WOLFENSTEIN3D_GAMESCREEN_H
#define WOLFENSTEIN3D_GAMESCREEN_H
#include "Camera.h"
#include "SDL2/SDL.h"

class GameScreen{
	Camera* camera;
	int h, w;
	SDL_Window* window;
	SDL_Renderer* renderer;

	public:

		GameScreen(Camera* camera, int h, int w);
		void draw();
		~GameScreen();
};

#endif