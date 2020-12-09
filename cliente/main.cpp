#include "GameScreen.h"
#include <unistd.h>
#include "Camera.h"

int main(){
	SDL_Event event;
	Camera camera(96 / 2, 96 / 2,0.66);
	GameScreen screen(&camera, 640, 480);
	bool done = false;
	while(!done){
		screen.draw();
        while (SDL_PollEvent(&event)) {
    		if (event.type == SDL_QUIT) done = true;
		}
		camera.rotate(0.01);
		usleep(3333);
	}
	return 0;
}