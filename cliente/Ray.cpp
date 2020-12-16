#include "Ray.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "SDL2/SDL.h"

Ray::Ray(Vector startPoint, Vector direction, int xPixel):
	xPixel(xPixel), startPoint(startPoint), direction(direction),
	deltaDistX(std::abs(1 / direction.x)),
	deltaDistY(std::abs(1 / direction.y)),
	collisionSide(0)
	{
		this->initialize(startPoint);
}

Ray::Ray(Camera* camera, double cameraX, int x):
	xPixel(x),
	startPoint(camera->getPosition()),
	direction(camera->getFacingPosition() + camera->getPlanePosition() * cameraX),
	deltaDistX(std::abs(1 / direction.x)),
	deltaDistY(std::abs(1 / direction.y)),
	collisionSide(0)
	{
		this->initialize(startPoint);
}

void Ray::initialize(Vector& position){
	if (direction.x < 0){
		this->stepX = -1;
		this->sideDistX = (position.x - 32 - position.scale().x * 32) 
							/ cos(direction.angle());
	} else {
		this->stepX = 1;
		this->sideDistX = (position.scale().x * 32 + 32 - position.x) 
							/ cos(direction.angle());
	}
	if (direction.y < 0){
		this->stepY = -1;
		this->sideDistY = (position.y - 32 - position.scale().y * 32) 
							/ sin(direction.angle());
	} else {
		this->stepY = 1;
		this->sideDistY = (position.scale().y * 32 + 32 - position.y) 
							/ sin(direction.angle());
	}
}

double Ray::distanceToWall(std::vector<std::vector<int>>& map){
	int mapX = startPoint.scale().x;
	int mapY = startPoint.scale().y;
	while (true){
		if (sideDistX < sideDistY){
			sideDistX += deltaDistX;
			mapX += stepX;
			collisionSide = 0;
		} else {
			sideDistY += deltaDistY;
			mapY += stepY;
			collisionSide = 1;
		}
		if (map[mapX][mapY] != 0){ // Guardar puntero a mapa
			break;
		}
	}
	return collisionSide == 0 ? (mapX - startPoint.x + (1 - stepX) / 2) / direction.x:
	 		(mapY - startPoint.y + (1 - stepY) / 2) / direction.y;
}

void Ray::draw(SDL_Renderer* renderer, int h, std::vector<std::vector<int>>& map){
	int lineHeight = (int) h * 10 / this->distanceToWall(map);
	int drawStart = std::max((h - lineHeight) / 2, 0);
	int drawEnd = std::min((h + lineHeight) / 2, h - 1);
	if (collisionSide){
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	} else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 255 / 2, SDL_ALPHA_OPAQUE);
	}
	SDL_RenderDrawLine(renderer, xPixel, drawStart, xPixel, drawEnd);
}

Ray::~Ray(){}
