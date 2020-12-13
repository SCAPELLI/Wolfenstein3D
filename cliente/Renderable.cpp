#include "Renderable.h"
#include <cmath>
#include "Ray.h"
#include <iostream>

#define PI 3.14159265

Renderable::Renderable(double x, double y, std::string path, SDL_Renderer* renderer):
	position(x,y), sprite(path, renderer){}


void Renderable::drawFrom(Camera* origin, std::vector<std::vector<int>>& map,
	SDL_Renderer* renderer){
	Vector originVector = origin->getPosition();
	double distance = position.distance(originVector);
	Vector direction = position - originVector;
	if (origin->getPlanePosition().angle(position) > 90){
		return;
	}
	double xPixel = (direction * cos(PI * origin->getPlanePosition().angle(position) / 180.0)).size();
	Ray ray(originVector, direction, xPixel);
	if (ray.distanceToWall(map) < distance) sprite.draw(renderer, xPixel, distance);
}

Renderable::~Renderable(){}