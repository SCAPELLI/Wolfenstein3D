//
// Created by juankristal on 21/2/21.
//

#include "BagOfSprites.h"
#include <string>
#define ROUTE "../Editor/sprites/sprite"
#define FILE_EXTENTION ".png"
#define ITEMS_SIZE 222

BagOfSprites::BagOfSprites(SDL_Renderer* renderer) {
    for (int i = 0; i < ITEMS_SIZE; i++){
        items[i] = std::move(Sprite(ROUTE + std::to_string(i) + FILE_EXTENTION, renderer));
    }
}

BagOfSprites::~BagOfSprites() {}