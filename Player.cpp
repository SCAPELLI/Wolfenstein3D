#include "Player.h"
#include <functional>
#include <iostream>
#include "Vector.h"
#define FULL_HEALTH 100
#define FULL_LIFE 3
#define INIT_ANGLE 0
#define RADIUS 2


Player::Player(int parsed_id, int init_x, int init_y)
:   id(parsed_id),
    lifes(FULL_LIFE),
    health(FULL_HEALTH),
    radius(RADIUS),
    angle(INIT_ANGLE),
    position(Vector(init_x, init_y))
{}
// bool Player::isTouched(Vector& other_position){
//     return this->collide(other_position);
// }

void Player::move(int dx, int dy){ // faltaria checkear si lo puede hacer o no
    position.add(dx, dy);
}

bool Player::collideWith(Player& other_player) {
    int dist = position.distance(other_player.getPosition());
    return dist < radius + other_player.radius;
}


Vector& Player::getPosition(){
    return position;
}

