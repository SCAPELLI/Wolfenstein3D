#include <SDL_image.h>
#include "client/include/Wall.h"
#include <string>
#include <iostream>
#define ROUTE "../../Editor/sprites/sprite"
#define FILE_EXTENTION ".png"

Wall::Wall(int id, SDL_Renderer* renderer){
    this->texture = IMG_LoadTexture(renderer, (ROUTE + std::to_string(id) + FILE_EXTENTION).c_str());
}

void Wall::drawLine(SDL_Renderer* renderer, int xPixel, int columnValue, int drawStart, int height){
    SDL_Rect src = {columnValue,0, 1, 32};
    SDL_Rect dest = {xPixel, drawStart, 1, std::abs(height)};
    SDL_RenderCopy(renderer, this->texture, &src, &dest);
}

Wall::~Wall(){
    SDL_DestroyTexture(texture);
}

