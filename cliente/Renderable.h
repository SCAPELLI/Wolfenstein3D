#ifndef WOLFENSTEIN3D_RENDERABLE_H
#define WOLFENSTEIN3D_RENDERABLE_H

#include <string>
#include "Map.h"
#include "Vector.h"
#include "SDL2/SDL.h"
#include "Sprite.h"
#include "Camera.h"

class Renderable{
	Vector position;
	Sprite sprite;
	public:
		Renderable(double x, double y, std::string path, SDL_Renderer* renderer);
		void drawFrom(Camera* origin,
			std::vector<std::vector<int>>& map,
			SDL_Renderer* renderer);
		~Renderable();
};

#endif