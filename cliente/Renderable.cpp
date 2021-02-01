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

int Renderable::findHorizontalPixel(SDL_Renderer* renderer, Vector& direction, Vector& relativePosition){
    int rw, rh;
    SDL_GetRendererOutputSize(renderer, &rw, &rh);
    int xPixel = int(rw / 2);
    double angle = direction.angle(relativePosition) * PI / 180;
    if (!isLeft(Vector(0,0), direction, relativePosition)){
        xPixel -= sin(angle) * int(rw / 2);
    } else {
        xPixel += sin(angle) * int(rw / 2);
    }
    return xPixel;
}

void Renderable::drawFrom(Camera* origin, std::vector<std::vector<int>>& map,
	SDL_Renderer* renderer){
    Vector referencePoint = origin->getPosition();
    Vector dividerVector = origin->getPlanePosition();
    Vector relativePosition = position - referencePoint;
    if (!isLeft(dividerVector, Vector(0,0), relativePosition)) return;

    double distance = position.distance(origin->getPosition());
    Ray ray(origin->getPosition(), position - origin->getPosition());
    double distanceToWall = ray.distanceToWallEuclidean(map);
    if (distanceToWall < distance) return;
    int xPixel = this->findHorizontalPixel(renderer, origin->getFacingPosition(), relativePosition);
    sprite.draw(renderer, xPixel, distance);
}

Renderable::~Renderable(){}