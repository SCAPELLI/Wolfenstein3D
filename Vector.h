
#ifndef WOLFENSTEIN3D_VECTOR_H
#define WOLFENSTEIN3D_VECTOR_H


class Vector {
public:
    int x;
    int y;
    int distance(Vector& otherVector);
public:
    Vector(int x, int y);
    Vector();
    Vector(Vector &&other);
    Vector& operator+=(Vector& otherPos);
    Vector& operator+(Vector& otherPos);
    int getX();
    int getY();
};


#endif //WOLFENSTEIN3D_VECTOR_H
