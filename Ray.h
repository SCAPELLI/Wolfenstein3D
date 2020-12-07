#include "Ray.h"

class Ray{
	Camera &camera;
	Vector direction;

	public:
		Ray(Camera &camera, double cameraX);
		double distanceToWall(Map &map);
		~Ray();
}
