#ifndef WOLFENSTEIN3D_GAMESCREEN_H
#define WOLFENSTEIN3D_GAMESCREEN_H
#include "Camera.h"
#include "SDL2/SDL.h"
#include "Renderable.h"
#include "Wall.h"
#include "CPlayer.h"
#include "UI.h"
#include <map>

class GameScreen{
	CPlayer* activePlayer;
	UI* ui;
	std::map<int, Wall*> wallTextures;
	SDL_Window* window;
	SDL_Renderer* renderer;

	public:

		GameScreen(CPlayer* player, int h, int w);
		SDL_Renderer* getRenderer();
		void draw(std::vector<std::vector<int>>& map,
			std::map<int, Renderable*>* renderables,
			std::map<int, CPlayer>* players);
		~GameScreen();
};

#endif