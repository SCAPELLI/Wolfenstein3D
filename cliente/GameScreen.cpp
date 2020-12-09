#include "GameScreen.h"
#include <algorithm>
#include <iostream>

GameScreen::GameScreen(Camera* camera, int h, int w):
	camera(camera),
    h(h),
    w(w){
        if (SDL_Init(SDL_INIT_VIDEO) == 0) {
            this->window = NULL;
            this->renderer = NULL;
        }
        SDL_CreateWindowAndRenderer(w, h, 0, &this->window, &this->renderer);
    }

void GameScreen::draw(){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    this->camera->draw(renderer, h, w);
    SDL_RenderPresent(renderer);
}


GameScreen::~GameScreen(){
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}
