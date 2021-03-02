#include "server/include/Player.h"
#include <cmath>
#include "server/include/Vector.h"
#include <vector>
#include "server/include/GameLoader.h"
#include "server/Items/Weapon.h"
#include "common/ServerEvents/AmmoChangeEvent.h"
#include "common/ServerEvents/ChangeWeaponEvent.h"
#include "common/ServerEvents/DoorOpenedEvent.h"
#include "common/ServerEvents/HealthChangeEvent.h"
#include "common/ServerEvents/PickUpKeyEvent.h"
#include "common/ServerEvents/PickUpWeaponEvent.h"
#include "common/ServerEvents/ScoreChangeEvent.h"
#include "common/Exception.h"
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
    YAML::Node fileNode = YAML::LoadFile("../../server/config/config.yaml");
    GameLoader yamlItems;
    if (!dead) {
        lifes = fileNode["Player"]["lifes"].as<int>();
        bulletsShot = fileNode["Player"]["bulletsShot"].as<int>();
        playersKilled = fileNode["Player"]["playersKilled"].as<int>();
        score = fileNode["Player"]["score"].as<int>();
        YAML::Node knifeNode = fileNode["Weapons"]["knife"];
        std::string nameWeapon = "knife";
        auto knife = Weapon(0, nameWeapon, 0, knifeNode["damage"].as<int>(),
          knifeNode["minBullets"].as<int>(), knifeNode["cooldownTimer"].as<int>());
        YAML::Node pistolNode = fileNode["Weapons"]["pistol"];
        std::string nameWeapon2 = "pistol";
        auto pistol = Weapon(1, nameWeapon2, 0, pistolNode["damage"].as<int>(),
          pistolNode["minBullets"].as<int>(), pistolNode["cooldownTimer"].as<int>());
        bag[0] = std::move(knife);
        bag[1] = std::move(pistol);
    }
    maxBullets = fileNode["Player"]["maxBullets"].as<int>();
    health = fileNode["Player"]["health"].as<int>();
    radius = fileNode["Player"]["radius"].as<int>();
    bullets = fileNode["Player"]["bullets"].as<int>();
    keys = fileNode["Player"]["key"].as<int>();
    angle = fileNode["Player"]["angle"].as<double>();
    speed = fileNode["Player"]["speed"].as<int>();
    idWeapon = 1;
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

double Player::angleWithOther(Player& otherPlayer) {
    Vector relativePosition = position - otherPlayer.position; //B
    Vector direction = Vector(-sin(angle), cos(angle)); //A
    double numerator = relativePosition * direction;
    double numeratosAbs = std::abs(numerator);
    double denominator = direction.size();
    double mult = denominator * relativePosition.size();
    double angleFinal = acos(numeratosAbs/mult);
    if (numerator > 0 ) return angleFinal + PI;
    return angleFinal;
}

int Player::damageCurrentWeapon() {
    return bag[idWeapon].getDamage();
}

void Player::move(Vector& newPos){
        position += newPos;
        scaledPosition = position.scale();
}

int Player::distanceWith(Player& otherPlayer) {
    return position.distance(otherPlayer.getPosition());
}
void Player::eraseCurrentWeapon(){
    bag.erase(idWeapon);
    prevIdWeapon = 1;
    idWeapon = 1;
    return;
}

void Player::updateBullets() {
    bullets -= bag[idWeapon].minBullets;
    bulletsShot += bag[idWeapon].minBullets;
}
bool Player::hasToChangeWeapon(){
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
    if (bag[idWeapon].name == "knife" && collideWith(distance, radius)
        && abs(deltaAngle) <= PI/6) {
        return true;
    }
    return  bag[idWeapon].doesHit(distance, deltaAngle) && deltaAngle <= PI/6;
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
    newEvents.push_back(new HealthChangeEvent(HealthChangeType, id, health));
    return true;
}

bool Player::getItem(PointGainItem* item,
                     std::vector<AbstractEvent*>& newEvents) {
    score += item->getEffect();
    newEvents.push_back(new ScoreChangeEvent(ScoreChangeType, id, item->getEffect()));
    return true;
}

bool Player::getItem(Weapon* item,
                     std::vector<AbstractEvent*>& newEvents) {
    return pickupWeapon(*item, newEvents);
}

bool Player::getItem(KeyItem* item,
                     std::vector<AbstractEvent*>& newEvents) {
    keys += item->getEffect();
    newEvents.push_back(new PickUpKeyEvent(PickUpKeyType, id));
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
    newEvents.push_back(new AmmoChangeEvent(AmmoChangeType, id, bullets));
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

int Player::getBullets() {
    return bullets;
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
int Player::getHealth(){
    return health;
}
int Player::getSpeed(){
    return speed;
}
Player::~Player() {}