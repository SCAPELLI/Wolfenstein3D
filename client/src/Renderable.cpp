#include "client/include/Renderable.h"
#include <cmath>
#include "client/include/Ray.h"
#include <iostream>

#define PI 3.14159265

Renderable::Renderable(double x, double y, Sprite* sprite):
	position(x,y), sprite(sprite){} // atributo animatedSprite y isAnimating?

void Renderable::drawOnScreen(SDL_Renderer* renderer, int posX, int posY, int scale){
    sprite->draw(renderer, posX, posY, scale);
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
    double transformX = invDet * (facingDirection.y * relativePosition.y / 32 - facingDirection.x * relativePosition.x / 32);
    double transformY = invDet * (-planeDirection.y * relativePosition.y / 32 + planeDirection.x * relativePosition.x / 32);
    sprite->rayCast(renderer, transformX, transformY, wallDistances);
}

void Renderable::moveTo(Vector& newPos){
    position = newPos;
}

Renderable::Renderable(Renderable&& other):
    position(std::move(other.position)), sprite(other.sprite){}

Renderable& Renderable::operator=(Renderable&& other){
    this->position = std::move(other.position);
    this->sprite = std::move(other.sprite);
    return *this;
}

Renderable::Renderable(): position(0,0){}

Renderable::~Renderable(){

}