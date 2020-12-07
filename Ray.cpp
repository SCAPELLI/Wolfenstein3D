#include "Ray.h"

Ray::Ray(Camera &camera, double cameraX):
	camera(camera),
	direction(camera.getFacingPosition() + camera.getPlanePosition() * cameraX),
	deltaDistX(std::abs(1 / direction.x)),
	deltaDistY(std::abs(1 / direction.y))
	{
		this.initialize();
	}

Ray::initialize(){
	if (direction.x < 0){
		this->stepX = -1;
		this->sideDistX = (camera.getPosition().x - camera.getPosition().scale().x) 
							* deltaDistX
	} else {
		this->stepX = 1;
		this->sideDistX = (camera.getPosition().scale().x + 1.0 - camera.getPosition().x) 
							* deltaDistX
	}
	if (direction.y < 0){
		this->stepY = -1;
		this->sideDistY = (camera.getPosition().y - camera.getPosition().scale().y) 
							* deltaDistY
	} else {
		this->stepY = 1;
		this->sideDistY = (camera.getPosition().scale().y + 1.0 - camera.getPosition().y) 
							* deltaDistY
	}
}

double Ray::distanceToWall(Map &map){
	int side;
	int mapX, mapY = camera.getPosition().scale().x, camera.getPosition.scale().y; 
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
		if (map.isWall(mapX, mapY)){
			break;
		}
	}
	return side ? (mapX - camera.getPosition().x + (1 - stepX) / 2) / direction.x:
			(mapY - camera.getPosition().y + (1 - stepY) / 2) / direction.y;
}



Ray::~Ray(){}
