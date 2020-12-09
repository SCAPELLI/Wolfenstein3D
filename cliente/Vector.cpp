#include "Vector.h"
#include <cmath>

Vector::Vector(double x, double y):
	x(x),
	y(y){}

Vector Vector::operator+(const Vector& v){
	return Vector(this->x + v.x, this->y + v.y);
}

void Vector::operator+=(const Vector& v){
	this->x += v.x;
	this->y += v.y;
}

double Vector::distance(const Vector& v){
	return pow(pow((this->x - v.x), 2) + pow((this->y - v.y), 2), 0.5);
}

double Vector::angle(){
	atan2(this->y, this->x);
}

Vector Vector::operator*(double z){
	return Vector(this->x * z, this->y * z);
}

Vector Vector::rotate(double degrees){
	return Vector(this->x * cos(-degrees) - this->y * sin(-degrees), 
			this->x * sin(-degrees) + this->y * cos(-degrees));
}

Vector Vector::scale(){ // Only scale positions
	return Vector(int(this->x / 32), int(this->y / 32)); // 32 hardcodeado, es tamanio de sprite
}

Vector::~Vector(){}