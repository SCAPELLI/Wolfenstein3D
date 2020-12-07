#include "Ray.h"

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
