#include "Player.h"
#include <cmath>
#include "Vector.h"
#include "GameLoader.h"
#include "Exception.h"
#include <iostream>
#define MAXBULLETS 50
#define MAXHEALTH 100
#define BULLET_ID 100
#define KEY_ID 101
#define POINT_ID 102

Player::Player(int parsed_id, Vector position)
:   id(parsed_id),
    position(position),
    initialPosition(position),
    scaledPosition(position.scale()),
    dead(false),
    maxBullets(MAXBULLETS)
{
    GameLoader yaml;
    yaml.configPlayer(lifes,
                      health,
                      radius,
                      angle,
                      bag,
                      idWeapon,
                      bullets,
                      points,
                      keys);
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
    throw Exception("No se encontró ese arma en el inventario");
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
    bullets = Item(BULLET_ID, "ammo", 8);
}
Weapon Player::getWeapon(){
    return bag[idWeapon];
}
bool Player::isDead(){
    return dead;
}
void Player::died(){
    lifes -=1;
    health = MAXHEALTH;
    position = initialPosition;
    scaledPosition = initialPosition.scale();\
    angle = 0;
    dead = false;
    points = PointGainItem();
    keys = KeyItem();
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

bool Player::getItem(LifeGainItem item) {
    if (health == MAXHEALTH) return false;
    health += item.getEffect();
    if (health > MAXHEALTH) {
        int extra = health % MAXHEALTH;
        health -= extra;
    }
    return true;
}

bool Player::getItem(PointGainItem item) {
    points.changeValue(item.getEffect());
    return true;
}
bool Player::getItem(Weapon item) {
    return pickupWeapon(item);
}
bool Player::getItem(KeyItem item) {
    keys.changeValue(item.getEffect());
    return true;
}
bool Player::getItem(Item item) {
    if (bullets.getEffect()  == maxBullets) return false;
    bullets.changeValue(item.getEffect());
    if (bullets.getEffect() > maxBullets) {
        int extra = bullets.getEffect() % maxBullets;
        bullets.changeValue(-extra);
    }
    return true;
}

bool Player::operator==(const Player& player){
    return player.id == this->id;
}