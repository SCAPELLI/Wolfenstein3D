#include "Screen.h"

Screen::Screen(double x, double y, double fov):
	camera(x, y, fov){}

//void Screen::updateCamera(UpdateEvent event){
//	event.run(this->camera);
//}

void Screen::draw(Map &map){
	for (int x = 0; x < 300; x++){//map.width; x++){ // w deberia ser el largo de la pantalla
		double cameraX = 2 * x / (double) 300 - 1;
		Ray ray(this->camera, cameraX);
		ray.draw(map);
	}
}

Screen::~Screen(){}
