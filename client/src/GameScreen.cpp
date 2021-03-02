#include "client/include/GameScreen.h"
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
        for (int i = 100; i < 205; i++){
            wallTextures[i] = new Wall(i, this->renderer);
        }
        this->ui = new UI(renderer, activePlayer);
}

bool distanceSort(std::pair<int, double> a, std::pair<int, double> b){
    return a.second > b.second;
}

void GameScreen::draw(std::vector<std::vector<int>>& map,
            std::map<int, Renderable>& renderables,
            std::map<int, EnemyPlayer*>& players){
    SDL_SetRenderDrawColor(renderer, 90, 90, 90, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 101, 67, 64, SDL_ALPHA_OPAQUE);
    SDL_Rect fillRect = {0, 240, 640, 240};
    SDL_RenderFillRect(renderer, &fillRect);
    std::vector<double> wallDistances;
    activePlayer->getCamera()->draw(renderer, map, &wallTextures, wallDistances);

    std::map<int, Renderable>::iterator it;
    std::vector<std::pair<int, double>> toDraw;
    for (it = renderables.begin(); it != renderables.end(); ++it){
        double distance = it->second.position.distance(activePlayer->getCamera()->getPosition());
            toDraw.push_back(std::make_pair(it->first, distance));
    }

    std::map<int, EnemyPlayer*>::iterator itPlayers;
    for (itPlayers = players.begin(); itPlayers != players.end(); ++itPlayers){
        double distance = itPlayers->second->position.distance(activePlayer->getCamera()->getPosition());
            toDraw.push_back(std::make_pair(itPlayers->first *-1, distance));

    }

    std::sort(toDraw.begin(), toDraw.end(), distanceSort);
    for (int i = 0; i < toDraw.size(); i++) {
        if (renderables.find(toDraw[i].first) != renderables.end()) {
            renderables[toDraw[i].first].drawFrom(activePlayer->getCamera(), map, renderer, wallDistances);
        } else {
            (*players[toDraw[i].first * -1]).drawFrom(activePlayer->getCamera(), map, renderer, wallDistances);
        }
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

