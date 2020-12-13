#include "Renderable.h"
#include <cmath>
#include "Ray.h"

Renderable::Renderable(double x, double y, int id, std::string& path, SDL_Renderer* renderer):
	position(x,y), id(id), sprite(path, renderer){}


void Renderable::drawFrom(Camera* origin, std::vector<std::vector<int>>& map,
	SDL_Renderer* renderer){
	Vector originVector = origin->getPosition();
	double distance = position.distance(originVector); // size
	Vector direction = position - originVector;
	if (origin->getPlanePosition().angle(position) > 180) return;
	double xPixel = (direction * cos(origin->getPlanePosition().angle(position))).size(); // quizas falta sumarle un offset
	Ray ray(originVector, direction, xPixel);
	if (ray.distanceToWall(map) < distance){
		sprite.draw(renderer, xPixel, (direction * sin(origin->getPlanePosition().angle(position))).size());
	}
}

Renderable::~Renderable(){}