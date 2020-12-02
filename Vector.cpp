
#include "Vector.h"
#include <cstdlib>

Vector::Vector(int x, int y) : x(x), y(y){}

int Vector::distance(Vector& other_vector) {
    return abs(x - other_vector.x) + abs(y - other_vector.y);
}

void Vector::add(int dx, int dy){
    x += dx;
    y += dy;
}