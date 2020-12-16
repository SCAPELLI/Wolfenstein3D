#ifndef WOLFENSTEIN3D_GAMESCREEN_H
#define WOLFENSTEIN3D_GAMESCREEN_H
#include "Camera.h"
#include "SDL2/SDL.h"
#include "Renderable.h"
#include "Player.h"
#include <map>

class GameScreen{
	Camera* camera;
	SDL_Window* window;
	SDL_Renderer* renderer;

	public:

		GameScreen(Camera* camera, int h, int w);
		SDL_Renderer* getRenderer();
		void draw(std::vector<std::vector<int>>& map,
			std::map<int, Renderable*>* renderables,
			std::map<int, Player>* players);
		~GameScreen();
};

#endif