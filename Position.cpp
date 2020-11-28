
#include "Position.h"
#include <cstdlib>

Position::Position(int x, int y) : x(x), y(y), radius(2){}

int Position::distance(int x2, int y2) {
    return abs(x - x2) + abs(y - y2);
}

bool Position::collide(Position other_position) {
    int dist = distance(other_position.x, other_position.y);
    return dist < radius + other_position.radius;
}


void Position::add(int dx, int dy){
    x += dx;
    y += dy;
}