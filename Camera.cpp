#include "Camera.h"

Camera::Camera(Vector cameraPosition, double fov):
	cameraPosition(cameraPosition),
	planePosition(0, fov),
	facingPosition(-1,0){}

void Camera::move(Vector direction){
	this->cameraPosition += direction;
}

void Camera::rotate(double grades){
	this->planePosition.rotate(grades);
}

Vector& Camera::getPosition(){
	return &this->cameraPosition;
}

Vector& Camera::getPlanePosition(){
	return &this->planePosition;
}

Vector& Camera::getFacingPosition(){
	return &this->facingPosition;
}

Camera::~Camera(){}
