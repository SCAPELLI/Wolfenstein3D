
#ifndef WOLFENSTEIN3D_POSITION_H
#define WOLFENSTEIN3D_POSITION_H


class Position {
public:
    int x;
    int y;
    int radius;
    int distance(int x, int y);
public:
    Position(int x, int y);
    bool collide(Position other_position);
    void add(int dx, int dy);
};


#endif //WOLFENSTEIN3D_POSITION_H
