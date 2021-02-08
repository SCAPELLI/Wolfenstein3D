#include "GameScreen.h"
#include <algorithm>
#include <iostream>

GameScreen::GameScreen(CPlayer* activePlayer, int h, int w):
	camera(activePlayer->getCamera()){
        if (SDL_Init(SDL_INIT_VIDEO) == 0) {
            this->window = NULL;
            this->renderer = NULL;
            SDL_CreateWindowAndRenderer(w, h, 0, &this->window, &this->renderer);
        }
        for (int i = 100; i < 158; i++){
            wallTextures[i] = new Wall(i, this->renderer);
        }
        this->ui = new UI(renderer, activePlayer);
}

void GameScreen::draw(std::vector<std::vector<int>>& map,
            std::map<int, Renderable*>* renderables,
            std::map<int, CPlayer>* players){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    std::vector<double> wallDistances;
    this->camera->draw(renderer, map, &wallTextures, wallDistances);
    std::map<int, Renderable*>::iterator it;
    for (it = renderables->begin(); it != renderables->end(); ++it){
        it->second->drawFrom(camera, map, renderer, wallDistances);
    }
    this->ui->draw(renderer);
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
    std::map<int, Wall*>::iterator it;
    for (it = wallTextures.begin(); it != wallTextures.end(); ++it){
        delete it->second;
    }
    delete this->ui;
    SDL_Quit();
}
