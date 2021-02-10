#include "CPlayer.h"

#define TOTAL_GUNS 4

CPlayer::CPlayer(double x, double y, double fov, int id):
	camera(x, y, fov), spawnPoint(x, y),
	hp(100), lives(3), ammo(10), activeWeapon(0), id(id){}

void CPlayer::loadWeapons(SDL_Renderer* renderer){
    for (int i = 0; i < TOTAL_GUNS; i++){
        weapons.emplace_back(new CWeapon(i, renderer));
    }
}


Camera* CPlayer::getCamera(){
	return &this->camera;
}

void CPlayer::moveTo(double x, double y){
	this->camera.moveTo(x,y);
}

void CPlayer::rotate(double degree){
	this->camera.rotate(degree);
}

void CPlayer::changeWeapon(int weaponID){
    weaponID = weaponID;
}

void CPlayer::drawWeapon(SDL_Renderer* renderer){
    int rw, rh;
    SDL_GetRendererOutputSize(renderer, &rw, &rh);
    weapons[activeWeapon]->draw(renderer, rw / 2, rh, 5);
}

void CPlayer::shoot(){
    weapons[activeWeapon]->shoot();
}

void CPlayer::respawn(){
	this->camera.moveTo(spawnPoint.x, spawnPoint.y);
	this->lives -= 1;
}

void CPlayer::decreaseLife(int damage){
	this->hp -= damage;
	if (this->hp < 0) this->respawn();
}

CPlayer::~CPlayer(){
    for (int i = 0; i < weapons.size(); i++) delete weapons[i];
}