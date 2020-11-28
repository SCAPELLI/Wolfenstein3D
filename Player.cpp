#include "Player.h"
#include <functional>
#include <iostream>

Player::Player(std::string name)
: id(), life(), position(Position(0, 0))
{}
bool Player::isTouched(Position& other_position){
    return position.collide(other_position);
}

void Player::move(int dx, int dy){ // faltaria checkear si lo puede hacer o no
    position.add(dx, dy);
}

Position& Player::getPosition(){
    return position;
}


int main(){
    Player p1("lu");
    Player p2 ("juani");
    p1.move(1, 1);
    std::cout<< p2.getPosition().x << p2.getPosition().y ;
    std::cout<< p1.getPosition().x << p1.getPosition().y ;
    std::cout<< p1.isTouched(p2.getPosition());



};