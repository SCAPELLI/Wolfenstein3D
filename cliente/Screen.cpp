#include "Screen.h"
#include "Ray.h"
#include <algorithm>
#include <iostream>

Screen::Screen(Camera* camera, int h, int w):
	camera(camera),
    h(h),
    w(w){
        if (SDL_Init(SDL_INIT_VIDEO) == 0) {
            this->window = NULL;
            this->renderer = NULL;
        }
        SDL_CreateWindowAndRenderer(w, h, 0, &this->window, &this->renderer);
    }

void Screen::draw(){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

   	for (int x = 0; x < w; x++){
		double cameraX = 2 * x / (double) w - 1;
		Ray ray(this->camera, cameraX, x);
		int lineHeight = (int) h * 10 / ray.distanceToWall();
		int drawStart = std::max((h - lineHeight) / 2, 0);
		int drawEnd = std::min((h + lineHeight) / 2, h - 1);
		if (ray.findCollisionSide()){
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		} else {
			SDL_SetRenderDrawColor(renderer, 0, 0, 255 / 2, SDL_ALPHA_OPAQUE);
		}
		SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
	}
    SDL_RenderPresent(renderer);
}


Screen::~Screen(){
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}
