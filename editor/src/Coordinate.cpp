#include "Coordinate.h"

#define BITS 32

Coordinate::Coordinate(size_t xInBits, size_t yInBits) {
    this->x = xInBits / BITS;
    this->y = yInBits / BITS;
}

size_t Coordinate::get_x() {
    return this->x;
}

size_t Coordinate::get_y() {
    return this->y;
}

bool Coordinate::operator<(const Coordinate &other) const {
    return this->x < other.x || this->x == other.x && this->y < other.y;
}
