#include "Screen.h"

Screen::Screen(double x, double y, double fov):
	camera(x, y, fov){}

void Screen::updateCamera(UpdateEvent event){
	event.run(this->camera);
}

void Screen::draw(){
	
}

Screen::~Screen(){}
