#ifndef WOLF_SPRITE_H
#define WOLF_SPRITE_H

#include <string>
#include "SDL2/SDL.h"
#include <vector>

class Sprite{
	int h, w;
	SDL_Texture* texture;
	public:
		Sprite(const std::string& path, SDL_Renderer* renderer);
		void rayCast(SDL_Renderer* renderer, double transformX, double transformY, std::vector<double> &wallDistances);
		void draw(SDL_Renderer* renderer, int posX, int posY, int scale);
        void drawLine(SDL_Renderer* renderer, int xPixel, int columnValue, int drawStart, int height);
		~Sprite();
};

#endif