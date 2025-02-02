#include "client/include/Camera.h"
#include "client/include/Ray.h"
#include <iostream>

Camera::Camera(double x, double y, double fov):
	cameraPosition(x,y),
	planePosition(0, fov),
	facingPosition(1,0),
	fov(fov){}

void Camera::moveTo(double x, double y){
	this->cameraPosition = Vector(x,y);
	//std::cout << "CLIENT\n";
	//std::cout << this->cameraPosition.x << "," << this->cameraPosition.y << "\n";
}

void Camera::rotate(double degrees){
	this->planePosition = this->planePosition.rotate(degrees);
	this->facingPosition = this->facingPosition.rotate(degrees);
}

void Camera::draw(SDL_Renderer* renderer,
                  std::vector<std::vector<int>>& map,
                  std::map<int, Wall*>* wallTextures,
                  std::vector<double> &wallDistances){
	int w, h;
	if (SDL_GetRendererOutputSize(renderer, &w, &h)) return;
   	for (int x = 0; x < w; x++){
		double cameraX = (2 * x / (double) w) - 1;
		Ray ray(this, cameraX, x);
		wallDistances.push_back(ray.drawWall(renderer, h, map, wallTextures));
	}
}

void Camera::resetVision(){
    planePosition = Vector(0, fov);
    facingPosition = Vector(1,0);
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
