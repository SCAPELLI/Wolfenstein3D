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
    position(std::move(position))
{}


void Player::move(Vector& newPos){
        position += newPos;
}


bool Player::collideWith(Player& other_player) {
    int dist = position.distance(other_player.getPosition());
    return dist < radius + other_player.radius;
}


Vector& Player::getPosition(){
    return position;
}

