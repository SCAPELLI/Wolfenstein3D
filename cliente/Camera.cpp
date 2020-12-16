#include "Camera.h"
#include "Ray.h"
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

void Camera::draw(SDL_Renderer* renderer, std::vector<std::vector<int>>& map){
	int w, h;
	if (SDL_GetRendererOutputSize(renderer, &w, &h)) return;
   	for (int x = 0; x < w; x++){
		double cameraX = 2 * x / (double) w - 1;
		Ray ray(this, cameraX, x);
		ray.draw(renderer, h, map);
	}
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
