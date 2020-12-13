#ifndef WOLFENSTEIN3D_RAY_H
#define WOLFENSTEIN3D_RAY_H
#include "Camera.h"
#include "Vector.h"
#include "SDL2/SDL.h"

class Ray{
	int xPixel;
	Vector startPoint;
	Vector direction;
	double deltaDistX, deltaDistY, sideDistX, sideDistY;
	int stepX, stepY, collisionSide;
	void initialize(Vector& position);
	public:
		double distanceToWall(std::vector<std::vector<int>>& map);
		Ray(Vector startPoint, Vector direction, int xPixel);
		Ray(Camera* camera, double cameraX, int x);
		void draw(SDL_Renderer* renderer, int h,
			std::vector<std::vector<int>>& map);
		~Ray();
};

#endif