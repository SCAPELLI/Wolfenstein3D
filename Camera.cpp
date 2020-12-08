#include "Camera.h"
#include <iostream>

Camera::Camera(double x, double y, double fov):
	cameraPosition(x,y),
	planePosition(0, fov),
	facingPosition(1,0){}

void Camera::move(Vector direction){
	this->cameraPosition += direction;
}

void Camera::rotate(double degrees){
	this->planePosition = this->planePosition.rotate(degrees);
	this->facingPosition = this->facingPosition.rotate(degrees);
}

Vector& Camera::getPosition(){
	return this->cameraPosition;
}

Vector& Camera::getPlanePosition(){
	return this->planePosition;
}

Vector& Camera::getFacingPosition(){
	return this->facingPosition;
}

Camera::~Camera(){}
