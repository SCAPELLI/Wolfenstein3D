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

void Renderable::drawFrom(Camera* origin,
                          std::vector<std::vector<int>>& map,
                          SDL_Renderer* renderer,
                          std::vector<double> &wallDistances){
    Vector referencePoint = origin->getPosition();
    Vector planeDirection = origin->getPlanePosition();
    Vector relativePosition = position - referencePoint;
    Vector facingDirection = origin->getFacingPosition();

    double invDet = 1.0 / (planeDirection.x * facingDirection.y - facingDirection.x * planeDirection.y);
    double transformX = invDet * (facingDirection.y * relativePosition.x / 32 - facingDirection.x * relativePosition.y / 32);
    double transformY = invDet * (-planeDirection.y * relativePosition.x / 32 + planeDirection.x * relativePosition.y / 32);
    sprite.draw(renderer, transformX, transformY, wallDistances);
}

Renderable::~Renderable(){}