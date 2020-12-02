#include "Camera.h"

Camera::Camera(Vector cameraPosition, double fov):
	cameraPosition(cameraPosition),
	planePosition(0, fov){}

void Camera::move(Vector direction){
	this->cameraPosition += direction;
}

void Camera::rotate(double grades){
	this->planePosition.rotate(grades);
}

Camera::~Camera(){}
