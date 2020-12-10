
#include "Vector.h"
#include <cstdlib>

Vector::Vector(int x, int y) : x(x), y(y){}

Vector::Vector() : x(0), y(0){}


//Vector::Vector(Vector &&other): x(other.x), y(other.y){}

int Vector::distance(Vector& otherVector) {
    return abs(x - otherVector.x) + abs(y - otherVector.y);
}

Vector& Vector::operator+=(Vector& otherPos){
    x += otherPos.x;
    y += otherPos.y;
    return *this;
}

Vector& Vector::operator+(Vector& otherPos){
    x += otherPos.x;
    y += otherPos.y;
    return *this;
}

int Vector::getX(){
    return x;
}
int Vector::getY(){
    return y;
}

 Vector& Vector::operator=(Vector&& other)noexcept{
     this->x = other.x;
     this->y = other.y;
     return *this;
 }

Vector::Vector(Vector&& other)
  :  x(other.x), y(other.y){
}