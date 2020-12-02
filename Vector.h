
#ifndef WOLFENSTEIN3D_VECTOR_H
#define WOLFENSTEIN3D_VECTOR_H


class Vector {
public:
    int x;
    int y;
    int distance(Vector& other_vector);
public:
    Vector(int x, int y);
    void add(int dx, int dy);// sobrecargar operador +
};


#endif //WOLFENSTEIN3D_VECTOR_H
