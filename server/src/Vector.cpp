#include "server/include/Vector.h"
#include <cmath>

#define PI 3.14159265

Vector::Vector(double x, double y):
	x(x),
	y(y){}

Vector Vector::operator+(const Vector& v){
	return Vector(this->x + v.x, this->y + v.y);
}
Vector Vector::operator/(double z){
	return Vector(this->x / z, this->y / z);
}

Vector Vector::operator-(const Vector& v){
	return Vector(this->x - v.x, this->y - v.y);
}
double Vector::operator*(Vector const &v) {
    return this.x * v.x + this.y * v.y;
}
void Vector::operator+=(const Vector& v){
	this->x += v.x;
	this->y += v.y;
}

double Vector::size(){
	return pow(x*x + y*y, 0.5);
}

double Vector::distance(const Vector& v){
	return pow(pow((this->x - v.x), 2) + pow((this->y - v.y), 2), 0.5);
}

double Vector::angle(){
	atan2(this->y, this->x) * 180.0 / PI;
}

double Vector::angle(const Vector& v){ 
	return acos((x * v.x + y * v.y) / (pow(x*x + y*y, 0.5) * pow(v.x * v.x + v.y * v.y, 0.5))) * 180.0 / PI;
}

Vector Vector::operator*(double z){
	return Vector(this->x * z, this->y * z);
}

Vector Vector::rotate(double degrees){
	return Vector(this->x * cos(-degrees) - this->y * sin(-degrees), 
			this->x * sin(-degrees) + this->y * cos(-degrees));
}

Vector Vector::scale(){ // Only scale positions
	return Vector(int(this->x / TILE), int(this->y / 32));
}

Vector::~Vector(){}
