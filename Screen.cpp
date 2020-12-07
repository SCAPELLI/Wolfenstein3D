#include "Screen.h"

Screen::Screen(double x, double y, double fov):
	camera(x, y, fov){}

void Screen::updateCamera(UpdateEvent event){
	event.run(this->camera);
}

void Screen::draw(Map &map){
	for (int x = 0; x < w; x++){
		double cameraX = 2 * x / (double) w - 1;
		Ray ray(this->camera, cameraX);
	}
}

Screen::~Screen(){}
