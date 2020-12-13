#include "Renderable.h"
#include <cmath>
#include "Ray.h"

Renderable::Renderable(double x, double y, int id, std::string sprite):
	position(x,y), id(id), sprite(sprite){}

void Renderable::updateSprite(std::string newSprite){
	this->sprite = newSprite;
}

void Renderable::drawFrom(Camera& origin){
	Vector originVector = origin.getPosition();
	double distance = position.distance(originVector); // size
	Vector direction = position - originVector;
	double xPixel = direction * cos(position.angle(camera.getPlanePosition())); // quizas falta sumarle un offset
	Ray ray(originVector, direction, xPixel);
	if (ray.distanceToWall() < distance){
		//draw sprite
	}
}

Renderable::~Renderable(){}