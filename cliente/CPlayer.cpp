#include "CPlayer.h"

CPlayer::CPlayer(double x, double y, double fov, int id):
	camera(x, y, fov), spawnPoint(x, y),
	hp(100), lifes(3), id(id){}

Camera* CPlayer::getCamera(){
	return &this->camera;
}

void CPlayer::moveTo(double x, double y){
	this->camera.moveTo(x,y);
}

void CPlayer::rotate(double degree){
	this->camera.rotate(degree);
}

void CPlayer::shoot(){}

void CPlayer::respawn(){
	this->camera.moveTo(spawnPoint.x, spawnPoint.y);
	this->lifes -= 1;
}

void CPlayer::decreaseLife(int damage){
	this->hp -= damage;
	if (this->hp < 0) this->respawn();
}

CPlayer::~CPlayer(){}