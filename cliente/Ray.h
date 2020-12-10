#ifndef WOLFENSTEIN3D_RAY_H
#define WOLFENSTEIN3D_RAY_H
#include "Camera.h"
#include "Vector.h"
#include "SDL2/SDL.h"

class Ray{
	int xPixel;
	Camera* camera;
	Vector direction;
	double deltaDistX, deltaDistY, sideDistX, sideDistY;
	int stepX, stepY, collisionSide;
	void initialize(Vector& position);
	public:
		int findCollisionSide();
		double distanceToWall();
		Ray(Camera* camera, double cameraX, int x);
		void draw(SDL_Renderer* renderer, int h);
		~Ray();
};

#endif