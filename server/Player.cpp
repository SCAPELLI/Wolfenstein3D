#include "Player.h"
#include <cmath>
#include "Vector.h"
#include "GameLoader.h"
#include <iostream>
#define INITIAL_BULLETS 8

Player::Player(int parsed_id, Vector position)
:   id(parsed_id),
    position(position)
{
    GameLoader yaml;
    yaml.configPlayer(lifes,
                      health,
                      radius,
                      angle,
                      bag);
}  // agregar bolsa de armas, posicion inicial

void Player::rotate(double newAngle){
    angle += newAngle;
}

double Player::getAngle() const {
    return angle;

}

void Player::move(Vector& newPos){
        position += newPos;
}

bool Player::hits(Player& otherPlayer) {
    std::cout << otherPlayer.position.x;
    int distance = position.distance(otherPlayer.position);
    int d = cos(angle) * distance;
    return abs(distance - d) < 0;
}
//int Player::changeWeaponTo(Weapon weapon){
//
//}
//
//bool Player::shoot(int idPlayer, int Weapon){
//
//
//}


int Player::lifeDecrement(int damage){
    health -= damage;
    if (health < 0 && lifes > 0){
        lifes -= 1;
        health = 100;
    }
    if (lifes == 0){
        return -1;
    }
    return damage;
}

bool Player::collideWith(Player& other_player) {
    int dist = position.distance(other_player.getPosition());
    return dist < radius + other_player.radius;
}


Vector& Player::getPosition(){
    return position;
}

