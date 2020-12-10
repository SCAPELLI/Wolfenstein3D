#include "Player.h"
#include <functional>
#include <iostream>
#include "Vector.h"
#define FULL_HEALTH 100
#define FULL_LIFE 3
#define INIT_ANGLE 0
#define RADIUS 2


Player::Player(int parsed_id, Vector position)
:   id(parsed_id),
    lifes(FULL_LIFE),
    health(FULL_HEALTH),
    radius(RADIUS),
    angle(INIT_ANGLE),
    position(position),
    weapon(1, 5)
{}

void Player::rotate(int newAngle){
    angle += newAngle % 360;
}

double Player::getAngle(){
    return angle;

}

void Player::move(Vector& newPos){
        position += newPos;
}

// Player& Player::operator=(Player&& otherPlayer) noexcept{
//     this->id = otherPlayer.id;
//     this->lifes = otherPlayer.lifes;
//     this->health = otherPlayer.health;
//     this->radius = otherPlayer.radius;
//     this->angle = otherPlayer.lifes;
//     this->position = std::move(otherPlayer.position);
//     this->weapon = otherPlayer.weapon;
//     return *this;
// }
//
//
// Player::Player(Player&& otherPlayer)
//     : id(otherPlayer.id),
//     lifes(otherPlayer.lifes),
//     health(otherPlayer.health),
//     radius(otherPlayer.radius),
//     angle(otherPlayer.lifes),
//     position(std::move(otherPlayer.position)),
//     weapon(otherPlayer.weapon)
// { }

void Player::lifeDecrement(int damage){
    health -= damage;
    if (health < 0 && lifes > 0){
        lifes -= 1;
    }
}

bool Player::collideWith(Player& other_player) {
    int dist = position.distance(other_player.getPosition());
    return dist < radius + other_player.radius;
}


Vector& Player::getPosition(){
    return position;
}

