#include "Player.h"

Player::Player(double x, double y, double fov, int id):
	camera(x, y, fov), spawnPoint(x, y),
	hp(100), lifes(3), id(id){}

Camera* Player::getCamera(){
	return &this->camera;
}

void Player::move(double x, double y){
	this->camera.move(Vector(x,y));
}

void Player::rotate(double degree){
	this->camera.rotate(degree);
}

void Player::shoot(){}

void Player::respawn(){
	this->camera.move(this->camera.getPosition() * -1);
	this->camera.move(spawnPoint);
	this->lifes -= 1;
}

void Player::decreaseLife(int damage){
	this->hp -= damage;
	if (this->hp < 0) this->respawn();
}

Player::~Player(){}