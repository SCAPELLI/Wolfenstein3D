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
