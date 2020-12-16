#include <string>
#include "SDL2/SDL.h"

class Sprite{
	int h, w;
	SDL_Texture* texture;
	public:
		Sprite(const std::string& path, SDL_Renderer* renderer);
		void draw(SDL_Renderer* renderer, int x, double distance);
		~Sprite();
};
