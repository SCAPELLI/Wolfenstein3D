#include "Screen.h"

Screen::Screen(double x, double y, double fov):
	camera(x, y, fov){}

void Screen::updateCamera(UpdateEvent event){
	event.run(this->camera);
}

void Screen::draw(){
	Vector mapPosition = camera.getPosition().scale()
	for (int x = 0; x < w; x++){
		double cameraX = 2 * x / (double) w - 1;
		Ray ray((camera.getPosition() + camera.getPlanePosition()) * cameraX);
	}
}

Screen::~Screen(){}
