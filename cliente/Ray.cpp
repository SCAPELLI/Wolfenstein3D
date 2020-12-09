#include "Ray.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

int worldMap[3][3]=
{ {1,1,1},
  {1,0,1},
  {1,1,1}
};

Ray::Ray(Camera* camera, double cameraX, int x):
	x(x),
	camera(camera),
	direction(camera->getFacingPosition() + camera->getPlanePosition() * cameraX),
	deltaDistX(std::abs(1 / direction.x)),
	deltaDistY(std::abs(1 / direction.y))
	{
		this->initialize();
	}

void Ray::initialize(){
	if (direction.x < 0){
		this->stepX = -1;
		this->sideDistX = (camera->getPosition().x - 32 - camera->getPosition().scale().x * 32) 
							/ cos(direction.angle());
	} else {
		this->stepX = 1;
		this->sideDistX = (camera->getPosition().scale().x * 32 + 32 - camera->getPosition().x) 
							/ cos(direction.angle());
	}
	if (direction.y < 0){
		this->stepY = -1;
		this->sideDistY = (camera->getPosition().y - 32 - camera->getPosition().scale().y * 32) 
							/ sin(direction.angle());
	} else {
		this->stepY = 1;
		this->sideDistY = (camera->getPosition().scale().y * 32 + 32 - camera->getPosition().y) 
							/ sin(direction.angle());
	}
}

int Ray::findCollisionSide(){
	int side;
	int mapX = camera->getPosition().scale().x;
	int mapY = camera->getPosition().scale().y;
	// std::cout << "Starting at (" << mapX << ", " << mapY << ")\n";
	while (true){
		if (sideDistX < sideDistY){
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
			// std::cout << "Updated mapX to" << mapX <<"\n";
		} else {
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
			// std::cout << "Updated mapY to" << mapY <<"\n";
		}
		if (worldMap[mapX][mapY]){//(map.isWall(mapX, mapY)){
			break;
		}
	}
	// std::cout << "Collision at (" << mapX << ", " << mapY << ")\n";
	// std::cout << "Direction from camera was " << direction.x << " " << direction.y << "\n\n";
	return side;
}

double Ray::distanceToWall(){//Map &map){
	int side;
	int mapX = camera->getPosition().scale().x;
	int mapY = camera->getPosition().scale().y;
	while (true){
		if (sideDistX < sideDistY){
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		} else {
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (worldMap[mapX][mapY]){//(map.isWall(mapX, mapY)){
			break;
		}
	}
	return side == 0 ? (mapX - camera->getPosition().x + (1 - stepX) / 2) / direction.x:
	 		(mapY - camera->getPosition().y + (1 - stepY) / 2) / direction.y;
}

void Ray::draw(){}

Ray::~Ray(){}
