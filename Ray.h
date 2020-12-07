#ifndef WOLFENSTEIN3D_RAY_H
#define WOLFENSTEIN3D_RAY_H
#include "Ray.h"
#include "Vector.h"

class Ray{
	Camera &camera;
	Vector direction;
	void initialize();
	double distanceToWall(Map &map);
	public:
		Ray(Camera &camera, double cameraX);
		void draw(Map &map);
		~Ray();
}

#endif