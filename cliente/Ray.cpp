#include "Ray.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "SDL2/SDL.h"

int worldMap[24][24]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

Ray::Ray(Camera* camera, double cameraX, int x):
	xPixel(x),
	camera(camera),
	direction(camera->getFacingPosition() + camera->getPlanePosition() * cameraX),
	deltaDistX(std::abs(1 / direction.x)),
	deltaDistY(std::abs(1 / direction.y)),
	collisionSide(0)
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

double Ray::distanceToWall(){
	int mapX = camera->getPosition().scale().x;
	int mapY = camera->getPosition().scale().y;
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
		if (worldMap[mapX][mapY]){ // Guardar puntero a mapa
			break;
		}
	}
	return collisionSide == 0 ? (mapX - camera->getPosition().x + (1 - stepX) / 2) / direction.x:
	 		(mapY - camera->getPosition().y + (1 - stepY) / 2) / direction.y;
}

void Ray::draw(SDL_Renderer* renderer, int h){
	int lineHeight = (int) h * 10 / this->distanceToWall();
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
