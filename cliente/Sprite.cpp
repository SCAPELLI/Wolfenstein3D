#include "Sprite.h"
#include "SDL2/SDL_image.h"

Sprite::Sprite(const std::string& path, SDL_Renderer* renderer){
	SDL_Surface* temp = nullptr;
	temp = IMG_Load(path.c_str());
	// manejar excepcion
	this->texture = SDL_CreateTextureFromSurface(renderer, temp);
	this->h = temp->h;
	this->w = temp->w;
	SDL_FreeSurface(temp);
}

void Sprite::draw(SDL_Renderer* renderer, int x, double distance){
	int rw, rh;
	SDL_GetRendererOutputSize(renderer, &rw, &rh);
	SDL_Rect source = {0,0, w, h};
	SDL_Rect dest = {(x - w / 2) / distance,
					((rw / 2) - h / 2) / distance, 
					(x + w / 2) / distance,
					((rw / 2) + h / 2) / distance};
	SDL_RenderCopy(renderer, this->texture, &source, &dest);
}

Sprite::~Sprite(){
	SDL_DestroyTexture(texture);
}