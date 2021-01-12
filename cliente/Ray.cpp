#include "Ray.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "SDL2/SDL.h"

Ray::Ray(Vector startPoint, Vector direction, int xPixel):
	xPixel(xPixel), startPoint(startPoint), direction(direction),
    deltaDistX(std::abs(1 / direction.y)),
    deltaDistY(std::abs(1 / direction.x)),
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
    int mapX = position.scale().y;
    int mapY = position.scale().x;
    double posX = position.y / 32;
    double posY = position.x / 32;
	if (direction.x < 0){
		this->stepX = -1;
        this->sideDistX = (posX - mapX) * deltaDistX;
	} else {
		this->stepX = 1;
        this->sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	}
	if (direction.y < 0){
		this->stepY = -1;
		this->sideDistY = (posY - mapY) * deltaDistY;
	} else {
		this->stepY = 1;
		this->sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	}
}

double Ray::distanceToWall(std::vector<std::vector<int>>& map){
	int mapX = startPoint.scale().y;
	int mapY = startPoint.scale().x;
	double posX = startPoint.y / 32;
    double posY = startPoint.x / 32;
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
	return collisionSide == 0 ? (mapX - posX + (1 - stepX) / 2) * deltaDistX:
	 		(mapY - posY + (1 - stepY) / 2) * deltaDistY;
}

void Ray::draw(SDL_Renderer* renderer, int h, std::vector<std::vector<int>>& map){
    double distance = this->distanceToWall(map);
	int lineHeight = (int) h / distance;
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
