#include "Player.h"
#include <cmath>
#include "Vector.h"
#include "GameLoader.h"
#include <iostream>

Player::Player(int parsed_id, Vector position)
:   id(parsed_id),
    position(position),
    initialPosition(position),
    gameOver(false)
{
    GameLoader yaml;
    yaml.configPlayer(lifes,
                      health,
                      radius,
                      angle,
                      bag);
}

void Player::rotate(double newAngle){
    angle += newAngle;
}

double Player::getAngle() const {
    return angle;
}

int Player::damageCurrentWeapon() {
    for (auto const& arm : bag) {
        if (arm.second)
            return arm.first.getDamage();
    }
    return 0;
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

void Player::pickupWeapon(Weapon weapon){ //dudoxso, cambiar el bag por nro id y el obj como clave y guardar como atributo id y un prev id
    for (auto const& arm : bag) {
        if (weapon == arm.first)
            return;
    }
    bag.insert(std::make_pair(weapon, false));
}

void Player::changeWeaponTo(Weapon weapon){
    for (auto const& arm : bag){
        if (arm.second)
            bag.insert(std::make_pair(arm.first, false));
    }
    bag[weapon] = true;  //a checkear
}

void Player::resetBagWeapons(){
    for (auto const& arm : bag) {
        if (arm.first.id != 0 && arm.first.id != 1)
            bag.erase(arm.first);
    }
}
void Player::died(){
    lifes -=1;
    health = 100;
    if (lifes <= 0){
        gameOver = true; // ver si es mejor marcarlo de otra forma--> tener un alive o no que lo marque?
    }
    position = initialPosition; //faltaria droppear los items
    angle = 0;
    resetBagWeapons();
}


int Player::lifeDecrement(int damage){
    health -= damage;
    if (health < 0)
       died();
    return damage;
}

bool Player::collideWith(Player& other_player) {
    int dist = position.distance(other_player.getPosition());
    return dist < radius + other_player.radius;
}


Vector& Player::getPosition(){
    return position;
}

