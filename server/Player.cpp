#include "Player.h"
#include <cmath>
#include "Vector.h"
#include <vector>
#include "GameLoader.h"
#include "../common/Items/AmmoItem.h"
#include "../common/ServerEvents/AmmoChangeEvent.h"
#include "../common/ServerEvents/ChangeWeaponEvent.h"
#include "../common/ServerEvents/DoorOpenedEvent.h"
#include "../common/ServerEvents/HealthChangeEvent.h"
#include "../common/ServerEvents/KillEvent.h"
#include "../common/ServerEvents/PickUpKeyEvent.h"
#include "../common/ServerEvents/PickUpWeaponEvent.h"
#include "../common/ServerEvents/ScoreChangeEvent.h"
#include "Exception.h"
#include <iostream>
#include "Event.h"
#define MAXHEALTH 100
#define KEY_ID 101

Player::Player(int parsed_id, Vector position)
:   id(parsed_id),
    position(position),
    initialPosition(position),
    scaledPosition(position.scale()),
    dead(false)
{
    initializePlayer(dead);
    prevIdWeapon = idWeapon;
}

void Player::initializePlayer(bool dead){
    YAML::Node fileNode = YAML::LoadFile("config.yaml");
    GameLoader yamlItems;
    maxBullets = fileNode["Player"]["maxBullets"].as<int>();
    if (!dead){
        lifes = fileNode["Player"]["lifes"].as<int>();
        points = PointGainItem();
    }
    health = fileNode["Player"]["health"].as<int>();
    radius = fileNode["Player"]["radius"].as<int>();
    bullets = AmmoItem(3, "ammo", fileNode["Player"]["bullets"].as<int>());
    angle = fileNode["Player"]["angle"].as<double>();
    int cont = 0;
    for (YAML::const_iterator it=fileNode["Weapons"].begin();
         it != fileNode["Weapons"].end(); ++it){
        std::string weaponType = it->first.as<std::string>();
        if(weaponType == "knife" || weaponType == "pistol"){
            YAML::Node data = fileNode["Weapons"][it->first.as<std::string>()];
            bag.insert(std::make_pair(cont,
                                      Weapon(cont, weaponType, data["damage"].as<int>(),
                                             data["minBullets"].as<int>(),
                                             data["speed"].as<double>())));
            idWeapon = cont;
        }
        cont++;
    }
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

bool Player::pickupWeapon(Weapon weapon,
                          std::vector<AbstractEvent*>& newEvents){
    for (auto const& arm : bag) {
        if (weapon == arm.second)
            return false;
    }
    bag.insert(std::make_pair(weapon.id, weapon));
    newEvents.push_back(new PickUpWeaponEvent(PickUpWeaponType,
                                                weapon.getUniqueId()));
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
    bullets = AmmoItem();
}
Weapon Player::getWeapon(){
    return bag[idWeapon];
}
bool Player::isDead(){
    return dead;
}
void Player::died(){
    lifes -=1;
    position = initialPosition;
    scaledPosition = initialPosition.scale();
    initializePlayer(dead);
    dead = false;
}

Item Player::getBullets(){
    return bullets;
}

void Player::KillEvent(int damage){
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

bool Player::getItem(LifeGainItem* item,
                     std::vector<AbstractEvent*>& newEvents) {
    if (health == MAXHEALTH){
     return false;
    }
    health += item->getEffect();
    if (health > MAXHEALTH) {
        int extra = health % MAXHEALTH;
        health -= extra;
    }
    newEvents.push_back(new HealthChangeEvent(HealthChangeType, health)); // hablar con juani
    return true;
}

bool Player::getItem(PointGainItem* item,
                     std::vector<AbstractEvent*>& newEvents) {
    points.changeValue(item->getEffect());
    newEvents.push_back(new ScoreChangeEvent(ScoreChangeType, item->getEffect()));
    return true;
}

bool Player::getItem(Weapon* item,
                     std::vector<AbstractEvent*>& newEvents) {
    return pickupWeapon(*item, newEvents);
}

bool Player::getItem(KeyItem* item,
                     std::vector<AbstractEvent*>& newEvents) {
    keys.changeValue(item->getEffect());
    newEvents.push_back(new PickUpKeyEvent(PickUpKeyType));
    return true;
}
bool Player::getItem(AmmoItem* item,
                     std::vector<AbstractEvent*>& newEvents) {
    if (bullets.getEffect()  == maxBullets) return false;
    bullets.changeValue(item->getEffect());
    if (bullets.getEffect() > maxBullets) {
        int extra = bullets.getEffect() % maxBullets;
        bullets.changeValue(-extra);
    }
    newEvents.push_back(new AmmoChangeEvent(AmmoChangeType, bullets.getEffect()));
    return true;
}

void Player::incrementCooldown() {
    for (auto  &arm : bag) {
        arm.second.incrementCooldown();
    }
}

bool Player::operator==(const Player& player){
    return player.id == this->id;
}

int Player::getId(){
    return id;
}