//
// Created by juankristal on 21/2/21.
//

#include "BagOfSprites.h"
#include <string>
#define ITEMS_ROUTE "../Editor/sprites/sprite"
#define ENEMY_SPRITES_ROUTE "../client/sprites/enemy_sprites/"
#define WEAPON_SPRITES_ROUTE "../client/sprites/weapons/"
#define ITEM_EXTENTION ".png"
#define ANIMATION_EXTENTION ".bmp"
#define ITEMS_SIZE 222
#define ANIMATION_SIZE 5
#define ENEMY_TYPES 5
#define WALKING_TYPE 0
#define SHOOTING_TYPE 1
#define DYING_TYPE 2

BagOfSprites::BagOfSprites(SDL_Renderer* renderer) {
    for (int i = 0; i < ITEMS_SIZE; i++){
        items[i] = std::move(Sprite(ITEMS_ROUTE + std::to_string(i) + ITEM_EXTENTION, renderer));
    }
    for (int i = 0; i < ENEMY_TYPES; i++){
        for (int j = 0; j < ANIMATION_SIZE; j++){
            animationSprites[WALKING_TYPE][std::make_pair(i,j)] = std::move(Sprite(ENEMY_SPRITES_ROUTE +
                    std::string("walking/") + std::to_string(i) + std::to_string(j) + ANIMATION_EXTENTION, renderer));
            animationSprites[SHOOTING_TYPE][std::make_pair(i,j)] = std::move(Sprite(ENEMY_SPRITES_ROUTE +
                    std::string("shooting/") + std::to_string(i) + std::to_string(j) + ANIMATION_EXTENTION, renderer));
            animationSprites[DYING_TYPE][std::make_pair(i,j)] = std::move(Sprite(ENEMY_SPRITES_ROUTE +
                    std::string("dying/") + std::to_string(i) + std::to_string(j) + ANIMATION_EXTENTION, renderer));
            weaponSprites[std::make_pair(i,j)] = std::move(Sprite(WEAPON_SPRITES_ROUTE + std::to_string(i) + std::to_string(j) +
                    ANIMATION_EXTENTION, renderer));
        }
    }
}

BagOfSprites::~BagOfSprites() {}