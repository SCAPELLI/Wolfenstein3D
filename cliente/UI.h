#ifndef WOLF_UI_H
#define WOLF_UI_H

#include "CPlayer.h"
#include <vector>
#include "SDL2/SDL.h"

class UI {
    CPlayer* activePlayer;
    SDL_Texture* HUD;
    std::vector<SDL_Texture*> numbers;
    public:
        UI(SDL_Renderer* renderer, CPlayer* activePlayer);
        void draw(SDL_Renderer* renderer);
        ~UI();
};


#endif //WOLF_UI_H
