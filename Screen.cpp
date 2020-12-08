#include "Screen.h"
#include "Ray.h"
#include <algorithm>
#include <iostream>
#include "SDL2/SDL.h"
#include <unistd.h>

Screen::Screen(double x, double y, double fov):
	camera(x, y, fov){}

//void Screen::updateCamera(UpdateEvent event){
//	event.run(this->camera);
//}

void Screen::draw(){//Map &map){
	int h = 640;
	int w = 480;
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(h, w, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

               	for (int x = 0; x < w; x++){//map.width; x++){ // w deberia ser el largo de la pantalla
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
                usleep(3333);

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }
                this->camera.rotate(0.001);
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
}

Screen::~Screen(){}
