#include "Renderable.h"
#include <cmath>
#include "Ray.h"
#include <iostream>

#define PI 3.14159265

Renderable::Renderable(double x, double y, std::string path, SDL_Renderer* renderer):
	position(x,y), sprite(path, renderer){} // atributo animatedSprite y isAnimating?

void Renderable::drawOnScreen(SDL_Renderer* renderer, int posX, int posY, int scale){
    sprite.draw(renderer, posX, posY, scale);
}

void Renderable::drawFrom(Camera* origin,
                          std::vector<std::vector<int>>& map,
                          SDL_Renderer* renderer,
                          std::vector<double> &wallDistances){
    Vector referencePoint = origin->getPosition();
    Vector planeDirection = origin->getPlanePosition();
    Vector relativePosition = position - referencePoint; // sistema de referencia
    Vector facingDirection = origin->getFacingPosition();

    double invDet = 1.0 / (planeDirection.x * facingDirection.y - facingDirection.x * planeDirection.y);
    double transformX = invDet * (facingDirection.y * relativePosition.x / 32 - facingDirection.x * relativePosition.y / 32);
    double transformY = invDet * (-planeDirection.y * relativePosition.x / 32 + planeDirection.x * relativePosition.y / 32);
    sprite.rayCast(renderer, transformX, transformY, wallDistances);
}

Renderable::~Renderable(){

}