#include "CPlayer.h"

#define TOTAL_GUNS 4

CPlayer::CPlayer(double x, double y, double fov, int id):
	camera(x, y, fov), spawnPoint(x, y),
	hp(100), lives(3), ammo(8), activeWeapon(1), score(0), id(id){}

void CPlayer::loadWeapons(SDL_Renderer* renderer, BagOfSprites& sprites){
    for (int i = 0; i < TOTAL_GUNS; i++){
        weapons.emplace_back(new CWeapon(i, sprites.weaponSprites));
    }
}

int CPlayer::getActiveWeapon() {
    return activeWeapon;
}

int CPlayer::getAmmo(){
    return ammo;
}

int CPlayer::getHp(){
    return hp;
}

int CPlayer::getLives(){
    return lives;
}

int CPlayer::getScore(){
    return score;
}

void CPlayer::increaseScore(int deltaScore) {
    score += deltaScore;
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
    activeWeapon = weaponID;
}

void CPlayer::drawWeapon(SDL_Renderer* renderer){
    int rw, rh;
    SDL_GetRendererOutputSize(renderer, &rw, &rh);
    weapons[activeWeapon]->draw(renderer, rw / 2, rh, 5);
}

bool CPlayer::shoot(){
    return weapons[activeWeapon]->shoot();
}

void CPlayer::respawn(){
	this->camera.moveTo(spawnPoint.x, spawnPoint.y);
    this->camera.resetVision();
	this->lives -= 1;
	this->hp = 100;
	this->activeWeapon = 1;
	this->ammo = 8;
}

void CPlayer::setHealth(int newHp){
	this->hp = newHp;
}

Vector CPlayer::getPosition() {
    return this->camera.getPosition();
}

CPlayer::~CPlayer(){
    for (int i = 0; i < weapons.size(); i++) delete weapons[i];
}

void CPlayer::changeAmmo(int newAmmo) {
    ammo = newAmmo;
}
