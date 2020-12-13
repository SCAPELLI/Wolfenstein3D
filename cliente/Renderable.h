#include <string>
#include "Map.h"
#include "Vector.h"
#include "SDL2/SDL.h"

class Renderable{
	Vector position;
	int id;
	std::string sprite
	public:
		Renderable(double x, double y, int id, std::string sprite);
		bool isOnSight(Map& map, Vector& origin);
		void updateSprite(std::string newSprite);
		void drawFrom(Camera& origin);
		~Renderable()
};
