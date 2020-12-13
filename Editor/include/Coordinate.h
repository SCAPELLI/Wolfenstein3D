#ifndef EDITOR_COORDINATE_H
#define EDITOR_COORDINATE_H

#include <cstdio>

class Coordinate {
    private:
        size_t x;
        size_t y;

    public:
        Coordinate(size_t xInBits, size_t yInBits);
        bool operator==(const Coordinate &other);
        bool operator<(const Coordinate &other) const;
};


#endif //EDITOR_COORDINATE_H
