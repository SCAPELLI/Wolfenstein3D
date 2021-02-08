#include <string>
#include "SDL2/SDL.h"
#include <vector>

class Sprite{
	int h, w;
	SDL_Texture* texture;
	public:
		Sprite(const std::string& path, SDL_Renderer* renderer);
		void draw(SDL_Renderer* renderer, double transformX, double transformY, std::vector<double> &wallDistances);
        void drawLine(SDL_Renderer* renderer, int xPixel, int columnValue, int drawStart, int height);
		~Sprite();
};
