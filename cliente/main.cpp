#include "Game.h"
#include <unistd.h>

int main(){
	SDL_Event event;
	Game game(96 / 2, 96 / 2,0.66);
	bool done = false;
	while(!done){
		game.draw();
        while (SDL_PollEvent(&event)) {
    		if (event.type == SDL_QUIT) done = true;
		}
		//camera.rotate(0.01);
		usleep(3333);
	}
	return 0;
}