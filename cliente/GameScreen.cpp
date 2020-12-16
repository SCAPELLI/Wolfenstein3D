#include "GameScreen.h"
#include <algorithm>
#include <iostream>

GameScreen::GameScreen(Camera* camera, int h, int w):
	camera(camera){
        if (SDL_Init(SDL_INIT_VIDEO) == 0) {
            this->window = NULL;
            this->renderer = NULL;
        }
        SDL_CreateWindowAndRenderer(h, w, 0, &this->window, &this->renderer);
    }

void GameScreen::draw(std::vector<std::vector<int>>& map,
            std::map<int, Renderable*>* renderables,
            std::map<int, CPlayer>* players){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    this->camera->draw(renderer, map);
    std::map<int, Renderable*>::iterator it;
    for (it = renderables->begin(); it != renderables->end(); ++it){
        it->second->drawFrom(camera, map, renderer);
    }
    SDL_RenderPresent(renderer);
}

SDL_Renderer* GameScreen::getRenderer(){
    return renderer;
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
