#include "Screen.h"
#include <unistd.h>
#include "Camera.h"

int main(){
	SDL_Event event;
	Camera camera(96 / 2, 96 / 2,0.66);
	Screen screen(&camera, 640, 480);
	while(true){
		screen.draw();
        while (SDL_PollEvent(&event)) {
    		if (event.type == SDL_QUIT) break;
		}
		camera.rotate(0.01);
		usleep(3333);
	}
	return 0;
}