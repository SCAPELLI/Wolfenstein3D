#ifndef WOLFENSTEIN3D_RAY_H
#define WOLFENSTEIN3D_RAY_H
#include "Camera.h"
#include "Vector.h"

class Ray{
	int x;
	Camera &camera;
	Vector direction;
	double deltaDistX, deltaDistY, sideDistX, sideDistY;
	int stepX, stepY;
	void initialize();
	//Map &map);
	public:
		int findCollisionSide();
		double distanceToWall();
		Ray(Camera &camera, double cameraX, int x);
		void draw();//Map &map);
		~Ray();
};

#endif