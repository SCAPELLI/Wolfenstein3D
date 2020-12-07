#ifndef WOLFENSTEIN3D_CAMERA_H
#define WOLFENSTEIN3D_CAMERA_H
#include "Vector.h"

class Camera{
	Vector cameraPosition;
	Vector planePosition;
	Vector facingPosition;

	public:
		Camera(Vector cameraPosition, double fov);
		void move(Vector direction);
		void rotate(double grades);
		Vector& getPosition();
		Vector& getPlanePosition();
		Vector& getFacingPosition();
		~Camera();
}

#endif