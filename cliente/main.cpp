#include "Game.h"
#include <unistd.h>

#define PI 3.14159265

int main(){
	SDL_Event event;
	Game game(96 / 2, 96 / 2,0.66);
	bool done = false;
	game.spawnRenderable();
	while(!done){
		game.draw();
        while (SDL_PollEvent(&event)) {
    		if (event.type == SDL_QUIT) done = true;
		}
		game.rotate(PI/180.0);
		usleep(3333);
	}
	return 0;
}