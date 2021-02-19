#include "GameScreen.h"
#include <algorithm>
#include <iostream>
#include <SDL_mixer.h>

GameScreen::GameScreen(CPlayer* activePlayer, int h, int w):
	activePlayer(activePlayer){
        if (SDL_Init(SDL_INIT_VIDEO) == 0) {
            this->window = NULL;
            this->renderer = NULL;
            SDL_CreateWindowAndRenderer(w, h, 0, &this->window, &this->renderer);
            Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
        }
        for (int i = 100; i < 163; i++){
            wallTextures[i] = new Wall(i, this->renderer);
        }
        this->ui = new UI(renderer, activePlayer);
}

bool distanceSort(std::pair<int, double> a, std::pair<int, double> b){
    return a.second < b.second;
}

void GameScreen::draw(std::vector<std::vector<int>>& map,
            std::map<int, Renderable*>* renderables,
            std::map<int, CPlayer>* players){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    std::vector<double> wallDistances;
    activePlayer->getCamera()->draw(renderer, map, &wallTextures, wallDistances);

    std::map<int, Renderable*>::iterator it;
    std::vector<std::pair<int, double>> toDraw;
    for (it = renderables->begin(); it != renderables->end(); ++it){
        double distance = it->second->position.distance(activePlayer->getCamera()->getPosition());
        if (distance < 150) {
            toDraw.push_back(std::make_pair(it->first, distance));
        }
    }
    std::sort(toDraw.begin(), toDraw.end(), distanceSort);
    for (int i = 0; i < toDraw.size(); i++) {
        (*renderables)[toDraw[i].first]->drawFrom(activePlayer->getCamera(), map, renderer, wallDistances);
    }

    this->ui->draw(renderer);
    activePlayer->drawWeapon(renderer);
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
