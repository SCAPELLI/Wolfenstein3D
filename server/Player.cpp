#include "Player.h"
#include <cmath>
#include "Vector.h"
#include <vector>
#include "GameLoader.h"
#include "Items/Weapon.h"
#include "../common/ServerEvents/AmmoChangeEvent.h"
#include "../common/ServerEvents/ChangeWeaponEvent.h"
#include "../common/ServerEvents/DoorOpenedEvent.h"
#include "../common/ServerEvents/HealthChangeEvent.h"
#include "../common/ServerEvents/PickUpKeyEvent.h"
#include "../common/ServerEvents/PickUpWeaponEvent.h"
#include "../common/ServerEvents/ScoreChangeEvent.h"
#include "Exception.h"
#include <iostream>
#include <limits>

#define PI 3.141592

#define MAXHEALTH 100


Player::Player(int parsed_id, int relativeId, std::string name, Vector position)
:   id(parsed_id),
    relativeId(relativeId),
    name(name),
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
    if (!dead){
        lifes = fileNode["Player"]["lifes"].as<int>();
        bulletsShot = fileNode["Player"]["bulletsShot"].as<int>();
        playersKilled = fileNode["Player"]["playersKilled"].as<int>();
        score = fileNode["Player"]["score"].as<int>();
        int cont = 0;
        for (YAML::const_iterator it=fileNode["Weapons"].begin();
             it != fileNode["Weapons"].end(); ++it){
            std::string weaponType = it->first.as<std::string>();
            if(weaponType == "knife" || weaponType == "pistol"){
                YAML::Node data = fileNode["Weapons"][it->first.as<std::string>()];
                auto equip = Weapon(cont, weaponType, 0, data["damage"].as<int>(),
                                    data["minBullets"].as<int>(),
                                    data["cooldownTimer"].as<int>());
                bag.insert(std::make_pair(cont, equip));
                idWeapon = cont;
            }
            cont++;
        }
    }
    maxBullets = fileNode["Player"]["maxBullets"].as<int>();
    health = fileNode["Player"]["health"].as<int>();
    radius = fileNode["Player"]["radius"].as<int>();
    bullets = fileNode["Player"]["bullets"].as<int>();
    keys = fileNode["Player"]["key"].as<int>();
    angle = fileNode["Player"]["angle"].as<double>();
}
void Player::setPosition(Vector initial){
    initialPosition = initial;
    position = initial;
    scaledPosition = initial.scale();
}


void Player::rotate(double newAngle){
    angle += newAngle;
    if (angle >= 2*PI)
        angle = angle - 2*PI;
    if (angle <= -2*PI)
        angle = angle + 2*PI;
}

double Player::getAngle() const {
    return angle;
}

double Player::angleWithOther(Player& otherPlayer){
    double angleWithOrigin = otherPlayer.getPosition().angle();
    return position.angle() - angleWithOrigin;
//    int deltaX = otherPlayer.getPosition().x - position.x; //adyacente
//    int distanceWith = position.distance(otherPlayer.position);
//    double angleWithOtherPlayer = acos(deltaX / distanceWith);
//    double deltaAngle = angleWithOtherPlayer - angle;
//    if ((deltaAngle)== 0) deltaAngle += 0.01;
//    return deltaAngle;
}

int Player::damageCurrentWeapon() { //borrar?
    return bag[idWeapon].getDamage();
}

void Player::move(Vector& newPos){
        position += newPos;
        scaledPosition = position.scale();
}

int Player::distanceWith(Player& otherPlayer) {
    return position.distance(otherPlayer.getPosition());
//    int distance = position.distance(otherPlayer.position); //distancia otro jugador
//    int d = cos(angle) * distance; // opuesto
//    if (abs(distance - d) < radius + otherPlayer.radius){
//        return distance;
//    }
//    return std::numeric_limits<int>::max();
}
void Player::eraseCurrentWeapon(){
    bag.erase(idWeapon);
    prevIdWeapon = 1;
    idWeapon = 1;
    return;
}

bool Player::shoot(){
    bullets -= bag[idWeapon].minBullets;
    bulletsShot += bag[idWeapon].minBullets;
    if (bullets < bag[idWeapon].minBullets && idWeapon != 0){
        prevIdWeapon = idWeapon;
        idWeapon = 0;
        return false;
    }
    return true;
}

int Player::hits(Player& otherPlayer){
    double deltaAngle = angleWithOther(otherPlayer);
    int distance = position.distance(otherPlayer.getPosition());
    int damage = bag[idWeapon].attack(distance,deltaAngle);
//    std::cout << "Se aplico " << damage << " de danio de " << id << " a " << otherPlayer.id << ".\n";
    return damage;
}

bool Player::hasRocketLauncher() {
    return bag[idWeapon].name == "rocket launcher";
}

Rocket* Player::setRocket(){
    Rocket* rocket = bag[idWeapon].launchRocket();
    rocket->sender = this;
    return rocket;
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

bool Player::changeWeaponTo(int idTochange){
    for (auto const& arm : bag){
        if (arm.first == idTochange) {
            prevIdWeapon = idWeapon;
            idWeapon = idTochange;
            return true;
        }
    }
    return false;
}

bool Player::hasKey(){
    return keys > 0;
}
void Player::resetBagWeapons(){
    for (auto const& arm : bag) {
        if (arm.first != 0 && arm.first != 1) //pierde las armas al final???
            bag.erase(arm.first);
    }
    idWeapon = 1;
    prevIdWeapon = 1;
}

Weapon Player::getWeapon(){
    return bag[idWeapon];
}

bool Player::isDead(){
    return dead;
}
void Player::respawn(){
    lifes -=1;
    position = initialPosition;
    scaledPosition = initialPosition.scale();
    initializePlayer(dead);
    dead = false;
}

int Player::getBullets(){
    return bullets;
}

int Player::getDamage(int damage) {
    health -= damage;
    if (health <= 0){
        dead = true;
        health = 0;
    }
    return health;
}

bool Player::collideWith(int distance, int radius) {
    return distance / TILE < radius + radius;
}

bool Player::canShoot() {
    return bag[idWeapon].canShoot(bullets) || bag[idWeapon].name == "knife";
}

bool Player::doesHit(Player& otherPlayer){
    double deltaAngle = angleWithOther(otherPlayer);
    int distance = position.distance(otherPlayer.getPosition());
    //std::cout << (bag[idWeapon].name == "knife") << "\n" << collideWith(distance, radius) << "paso el collide \n";
    if (bag[idWeapon].name == "knife" && collideWith(distance, radius)
        && deltaAngle <= PI/3) {
        return true;
    }
    return bag[idWeapon].doesHit(distance, deltaAngle) && deltaAngle <= PI/3;
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
    if (keys > 0) {
        keys -= 1;
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
    newEvents.push_back(new HealthChangeEvent(HealthChangeType, health, id));
    return true;
}

bool Player::getItem(PointGainItem* item,
                     std::vector<AbstractEvent*>& newEvents) {
    score += item->getEffect();
    newEvents.push_back(new ScoreChangeEvent(ScoreChangeType, item->getEffect()));
    return true;
}

bool Player::getItem(Weapon* item,
                     std::vector<AbstractEvent*>& newEvents) {
    return pickupWeapon(*item, newEvents);
}

bool Player::getItem(KeyItem* item,
                     std::vector<AbstractEvent*>& newEvents) {
    keys += item->getEffect();
    newEvents.push_back(new PickUpKeyEvent(PickUpKeyType));
    return true;
}

bool Player::getItem(AmmoItem* item,
                     std::vector<AbstractEvent*>& newEvents) {
    if (bullets == maxBullets) return false;
    bullets += item->getEffect();
    if (bullets > maxBullets) {
        int extra = bullets % maxBullets;
        bullets -= extra;
    }
    newEvents.push_back(new AmmoChangeEvent(AmmoChangeType, bullets, id));
    return true;
}

void Player::incrementCooldown() {
    for (auto it=bag.begin(); it!=bag.end(); ++it){
        (it->second).incrementCooldown();
    }
}

bool Player::operator==(const Player& player) const{
    return player.id == this->id;
}

int Player::getId() const {
    return id;
}

void Player::updateKills(){
    playersKilled+=1;
}

int Player::getLifes() const {
    return lifes;
}
Vector Player::getInitialPosition(){
    return initialPosition;
}
int Player::getEnemiesKilled(){
    return playersKilled;
}
int Player::getBulletsShoot(){
    return bulletsShot;
}
int Player::getScore(){
    return score;
}
std::string Player::getName(){
    return name;
}
Player::~Player() {}