#include "Player.h"
#include <cmath>
#include "Vector.h"
#include "GameLoader.h"
#include <iostream>
#define MAXBULLETS 50
#define BULLET_ID 100
#define KEY_ID 101
#define COIN_ID 102

Player::Player(int parsed_id, Vector position)
:   id(parsed_id),
    position(position),
    initialPosition(position),
    scaledPosition(position.scale()),
    dead(false),
    coins(Item(COIN_ID,0)),
    keys(Item(KEY_ID,0)),
    maxBullets(MAXBULLETS)
{
    GameLoader yaml;
    yaml.configPlayer(lifes,
                      health,
                      radius,
                      angle,
                      bag,
                      idWeapon,
                      bullets);
    prevIdWeapon = idWeapon;
}

void Player::rotate(double newAngle){
    angle += newAngle;
}

double Player::getAngle() const {
    return angle;
}

int Player::damageCurrentWeapon() { //borrar?
    return bag[idWeapon].getDamage();
}

void Player::move(Vector& newPos){
        position += newPos;
        scaledPosition = position.scale();
}

bool Player::hits(Player& otherPlayer) {
    int distance = position.distance(otherPlayer.position);
    int d = cos(angle) * distance;
    if (abs(distance - d) < radius + otherPlayer.radius){
        return true; //distance???
    }
    return false;
}

bool Player::pickupWeapon(Weapon weapon){
    for (auto const& arm : bag) {
        if (weapon == arm.second)
            return false;
    }
    bag.insert(std::make_pair(weapon.id, weapon));
    return true;
}

void Player::changeWeaponTo(int idTochange){ //antes recibia weapon no se que es mejor o que se recibe del cliente
    for (auto const& arm : bag){
        if (arm.first == idTochange) {
            prevIdWeapon = idWeapon;
            idWeapon = idTochange;
        }
    }
    // error que no se encontro??
}
bool Player::hasKey(){
    return keys.getEffect() > 0;
}
void Player::resetBagWeapons(){
    for (auto const& arm : bag) {
        if (arm.first != 0 && arm.first != 1)
            bag.erase(arm.first);
    }
    idWeapon = 1;
    prevIdWeapon = 1;
    bullets = Item(BULLET_ID, 8);
}
Weapon Player::getWeapon(){
    return bag[idWeapon];
}
bool Player::isDead(){
    return dead;
}
void Player::died(){
    lifes -=1;
    health = 100;
//    if (lifes <= 0){
//        dead = true; // ver si es mejor marcarlo de otra forma--> tener un alive o no que lo marque?
//    }
    position = initialPosition;
    scaledPosition = initialPosition.scale();\
    angle = 0;
    dead = false;
    coins = Item(COIN_ID, 0);
    keys = Item(KEY_ID, 0);
    resetBagWeapons();
}

Item Player::getBullets(){
    return bullets;
}

void Player::lifeDecrement(int damage){
    health -= damage;
    if (health <= 0)
       dead = true;
}

bool Player::collideWith(Player& other_player) {
    int dist = position.distance(other_player.getPosition());
    return dist < radius + other_player.radius;
}


Vector& Player::getPosition(){
    return position;
}
Vector& Player::getScaledPosition(){
    return scaledPosition;
}
bool Player::isGameOver(){
    return dead && lifes <= 0;
}

bool Player::openDoor(){
    if (keys.getEffect() > 0) {
        keys.changeValue(-1);
        return true;
    }
    return false;
}

bool Player::getItem(int idItem){

    switch (idItem) {
        case 0:  // es comida
            if (health == 100) return false;
            health += 10;
            break;
        case 1:     //kit medico
            if (health == 100) return false;
            health += 20;
            break;
        case 2: // sangre
            if (health >= 10) return false;
            health += 1;
            break;
        case 3:
            if (bullets.getEffect() + 5 > maxBullets) return false;
            bullets.changeValue(5); // fijarme si tiene las balas máximas
            break;
        case 4:
            return pickupWeapon(Weapon(2, 5, 5, 0.3));
        case 5:
            return pickupWeapon(Weapon(3, 5, 5, 0.3));
        case 6:
            return pickupWeapon(Weapon(4, 5, 5, 0.3));
        case 7:
            coins.changeValue(10); // ver que tipo de tesoro es
            break;
        case 8:
            keys.changeValue(1);
            break;
        default:
            return false;
    }
    return true;
}

bool Player::operator==(const Player& player){
    return player.id == this->id;
}