#include "Sprite.h"
#include "SDL2/SDL_image.h"
#include <iostream>

Sprite::Sprite(const std::string& path, SDL_Renderer* renderer){
	SDL_Surface* temp = nullptr;
	std::cout << path << "\n";
	temp = SDL_LoadBMP(path.c_str());
	// manejar excepcion
	this->texture = SDL_CreateTextureFromSurface(renderer, temp);
	this->h = temp->h;
	this->w = temp->w;
	SDL_FreeSurface(temp);
}

void Sprite::draw(SDL_Renderer* renderer, int x, double distance){
	int rw, rh;
	SDL_GetRendererOutputSize(renderer, &rw, &rh);
	std::cout << x << "\n";
	distance = 1;
	SDL_Rect dest = {(x - w / 2) / distance,
					((rw / 2) - h / 2) / distance, 
					(x + w / 2) / distance,
					((rw / 2) + h / 2) / distance};
	SDL_RenderCopy(renderer, this->texture, NULL, &dest);
}

Sprite::~Sprite(){
	SDL_DestroyTexture(texture);
}