#include "Vector.h"

class Camera{
	Vector cameraPosition;
	Vector planePosition;

	public:
		Camera(Vector cameraPosition, double fov);
		void move(Vector direction);
		void rotate(double grades);
		~Camera();
}
