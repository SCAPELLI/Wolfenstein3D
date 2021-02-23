//
// Created by juankristal on 8/2/21.
//

#define ANIMATED_FRAMES 5
#define ANIMATED_TIME 15
#include "CWeapon.h"
#define ROUTE "../cliente/sprites/weapons/"


CWeapon::CWeapon(int weaponID, std::map<std::pair<int, int>, Sprite>& sprites):
    animatedSprite(sprites, Vector(0,0), weaponID, ANIMATED_FRAMES, ANIMATED_TIME){}

bool CWeapon::shoot(){
    if (animatedSprite.isAnimating) return false;
    animatedSprite.isAnimating = true;
    return true;
}

void CWeapon::draw(SDL_Renderer* renderer, int posX, int posY, int scale){
    animatedSprite.draw(renderer, posX, posY, scale);
}

CWeapon::~CWeapon() {}