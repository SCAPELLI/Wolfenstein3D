#include "Renderable.h"
#include <cmath>
#include "Ray.h"
#include <iostream>

#define PI 3.14159265

Renderable::Renderable(double x, double y, std::string path, SDL_Renderer* renderer):
	position(x,y), sprite(path, renderer){}

bool isLeft(Vector a, Vector b, Vector c){
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x) > 0;
}

void Renderable::drawFrom(Camera* origin, std::vector<std::vector<int>>& map,
	SDL_Renderer* renderer){
	Vector originVector = origin->getPosition();
	double distance = position.distance(originVector);
	Vector direction = position - originVector;
	double angle = origin->getFacingPosition().angle(direction);
	//if (angle > 90) return;
	double xPixel = 320 + 320 * cos(PI * angle / 180.0); // verificar si es visible
	if (!isLeft(origin->getFacingPosition(), Vector(0,0), direction * (1/direction.size()))) xPixel += 2 * (240 - xPixel);
    std::cout << xPixel << "\n";
	Ray ray(originVector, direction, xPixel);
	if (ray.distanceToWall(map) < distance) sprite.draw(renderer, xPixel, distance);
}

Renderable::~Renderable(){}