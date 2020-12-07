#ifndef WOLFENSTEIN3D_SCREEN_H
#define WOLFENSTEIN3D_SCREEN_H
#include "Camera.h"

class Screen{
	Camera camera;

	public:

		Screen(double x, double y, double fov);
		//void updateCamera(UpdateEvent event);
		void draw(Map &map);
		~Screen();
}

#endif