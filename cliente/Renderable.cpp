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
    Vector referencePoint = origin->getPosition();
    Vector dividerVector = origin->getPlanePosition();
    Vector relativePosition = position - referencePoint;
    if (!isLeft(dividerVector, Vector(0,0), relativePosition)) return;

    double distance = position.distance(origin->getPosition());
    Ray ray(origin->getPosition(), position - origin->getPosition());
    if (!ray.closerToWallThan(map, position.scale().y, position.scale().x)) sprite.draw(renderer, 220, distance);
//	Vector originVector = origin->getPosition();
//	double distance = position.distance(originVector);
//	Vector direction = position - originVector;
//	double angle = origin->getFacingPosition().angle(direction) - 90;
//	if (angle > 90 || angle < -90) return;
//	double xPixel = 320 + 320 * cos(PI * angle / 180.0); // verificar si es visible
//	if (!isLeft(origin->getFacingPosition(), Vector(0,0), direction * (1/direction.size()))) xPixel += 2 * (240 - xPixel);
//	Ray ray(originVector, direction, xPixel);
//	if (xPixel < 0 || xPixel > 480) return;
//	if (ray.distanceToWall(map) > distance) sprite.draw(renderer, xPixel, distance);
}

Renderable::~Renderable(){}