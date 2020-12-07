#include "Camera.h"

class Screen{
	Camera camera;

	public:

		Screen(double x, double y, double fov);
		void updateCamera(UpdateEvent event);
		void draw(Map &map);
		~Screen();
}
