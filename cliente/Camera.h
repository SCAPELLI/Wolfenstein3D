#ifndef WOLFENSTEIN3D_CAMERA_H
#define WOLFENSTEIN3D_CAMERA_H
#include "Vector.h"
#include "SDL2/SDL.h"

class Camera{
	Vector cameraPosition;
	Vector planePosition;
	Vector facingPosition;

	public:
		Camera(double x, double y, double fov);
		void move(Vector direction);
		void rotate(double degrees);
		void draw(SDL_Renderer* renderer, int h, int w);
		Vector& getPosition();
		Vector& getPlanePosition();
		Vector& getFacingPosition();
		~Camera();
};

#endif