//
// Created by juankristal on 8/2/21.
//

#define ANIMATED_FRAMES 5
#define ANIMATED_TIME 15
#include "CWeapon.h"
#define ROUTE "../cliente/sprites/weapons/"


CWeapon::CWeapon(int weaponID, SDL_Renderer *renderer):
    animatedSprite(ROUTE + std::to_string(weaponID) + "-", renderer, ANIMATED_FRAMES, ANIMATED_TIME){

}

bool CWeapon::shoot(){
    if (animatedSprite.isAnimating) return false;
    animatedSprite.isAnimating = true;
    return true;
}

void CWeapon::draw(SDL_Renderer* renderer, int posX, int posY, int scale){
    animatedSprite.draw(renderer, posX, posY, scale);
}

CWeapon::~CWeapon() {}