#include "Player.h"
#include <cmath>
#include "Vector.h"
#include "GameLoader.h"
#include <iostream>

Player::Player(int parsed_id, Vector position)
:   id(parsed_id),
    position(position),
    initialPosition(position),
    gameOver(false),
    coins(0),
    keys(0)
{
    GameLoader yaml;
    yaml.configPlayer(lifes,
                      health,
                      radius,
                      angle,
                      bag,
                      idWeapon);
}

void Player::rotate(double newAngle){
    angle += newAngle;
}

double Player::getAngle() const {
    return angle;
}

int Player::damageCurrentWeapon() {
    return bag[idWeapon].getDamage();
}

void Player::move(Vector& newPos){
        position += newPos;
}

bool Player::hits(Player& otherPlayer) {
    std::cout << otherPlayer.position.x;
    int distance = position.distance(otherPlayer.position);
    int d = cos(angle) * distance;
    if (abs(distance - d) < radius + otherPlayer.radius){
        return true; //distance???
    }
    return false;
}

void Player::pickupWeapon(Weapon weapon){
    for (auto const& arm : bag) {
        if (weapon == arm.second)
            return;
    }
    bag.insert(std::make_pair(weapon.id, weapon));
}

void Player::changeWeaponTo(int idTochange){ //antes recibia weapon no se que es mejor o que se recibe del cliente
    for (auto const& arm : bag){
        if (arm.first == idTochange) {
            idWeapon = idTochange;
        }
    }
    // error que no se encontro??
}

void Player::resetBagWeapons(){
    for (auto const& arm : bag) {
        if (arm.first != 0 && arm.first != 1)
            bag.erase(arm.first);
    }
    idWeapon = 1;
    bag[1].bullets = 8;
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


void Player::lifeDecrement(int damage){
    health -= damage;
    if (health < 0)
       died();
}

bool Player::collideWith(Player& other_player) {
    int dist = position.distance(other_player.getPosition());
    return dist < radius + other_player.radius;
}


Vector& Player::getPosition(){
    return position;
}
bool Player::isGameOver(){
    return gameOver;
}

bool Player::openDoor(){
    if (keys > 0) {
        keys -= 1;
        return true;
    }
    return false;
}

void Player::getItem(int idItem){
    //if (health == 100) return;
    switch (idItem) { // es comida
        case 0:
                health += 10;
            break;
        case 1:     //kit medico
                health += 20;
            break;
        case 2: // sangre
                health += 1;
            break;
        case 3:
            bag[idWeapon].addBullets(5);
            break;
        case 4:
            pickupWeapon(Weapon(2, 5, 0, 5, 0.3));
            break;
        case 5:
            pickupWeapon(Weapon(3, 5, 0, 5, 0.3));
            break;
        case 6:
            pickupWeapon(Weapon(4, 5, 0, 5, 0.3));
            break;
        case 7:
            coins += 10; // ver que tipo de tesoro es
            break;
        case 8:
            keys += 1;
    }
}

