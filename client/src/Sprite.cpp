#include "client/include/Sprite.h"
#include "SDL2/SDL_image.h"
#include <iostream>

Sprite::Sprite(const std::string& path, SDL_Renderer* renderer){
	SDL_Surface* temp = nullptr;
	temp = IMG_Load(path.c_str());
	// manejar excepcion
	if (!temp) return;
	Uint32 transparentKey = SDL_MapRGB(temp->format, 152, 0, 136);
	SDL_SetColorKey(temp, SDL_TRUE, transparentKey);
	this->texture = SDL_CreateTextureFromSurface(renderer, temp);
	this->h = temp->h;
	this->w = temp->w;
	SDL_FreeSurface(temp);
}

void Sprite::draw(SDL_Renderer* renderer, int posX, int posY, int scale){
    SDL_Rect dest = {posX - (w * scale) / 2, posY - 64 - h * scale, w * scale, h * scale};
    SDL_RenderCopy(renderer, this->texture, NULL, &dest);
}

void Sprite::rayCast(SDL_Renderer* renderer, double transformX, double transformY, std::vector<double> &wallDistances){
    int rw, rh;
    SDL_GetRendererOutputSize(renderer, &rw, &rh);

    int spriteScreenX = int((rw / 2) * (1 + transformX / transformY));
    int spriteHeight = std::abs(int(rh / (transformY)));
    int startY = std::max(-spriteHeight / 2 + rh / 2, 0);
    int endY = std::min(spriteHeight / 2 + rh / 2, rh - 1);
    int startX = std::max(-spriteHeight / 2 + spriteScreenX, 0);
    int endX = std::min(spriteHeight / 2 + spriteScreenX, rw - 1);

    for (int stripe = startX; stripe < endX; stripe++){
        int texX = int(256 * (stripe - (-spriteHeight / 2 + spriteScreenX)) * w / spriteHeight) / 256;
        if (stripe <= 0 || stripe >= rw || transformY <= 0 || transformY >= wallDistances[stripe])
            continue;
        this->drawLine(renderer, texX, stripe, startY, endY);
    }
}

void Sprite::drawLine(SDL_Renderer* renderer, int texX, int xPixel, int drawStart, int height){
    SDL_Rect src = {texX,0, 1, h};
    SDL_Rect dest = {xPixel, drawStart, 1, std::abs(height - drawStart)};
    SDL_RenderCopy(renderer, this->texture, &src, &dest);
}

Sprite::Sprite(){}

Sprite::~Sprite(){
	if (texture != nullptr)
        SDL_DestroyTexture(texture);
}

Sprite::Sprite(Sprite &&other): h(other.h), w(other.w), texture(other.texture){
    other.texture = nullptr;
}

Sprite &Sprite::operator=(Sprite &&other) {
    this->h = std::move(other.h);
    this->w = std::move(other.w);
    this->texture = other.texture;
    other.texture = nullptr;
    return *this;
}
