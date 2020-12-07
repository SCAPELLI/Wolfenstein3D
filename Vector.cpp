#include "Vector.h"

Vector::Vector(double x, double y):
	x(x),
	y(y){}

Vector Vector::operator+(const Vector& v){
	return Vector(this->x + v.x, this->y + v.y);
}

Vector Vector::operator*(double z){
	return Vector(this->x * z, this->y * z);
}

Vector Vector::scale(){ // Only scale positions
	return Vector(int(this->x / 32), int(this->y / 32)); // 32 hardcodeado
}

Vector::~Vector(){}