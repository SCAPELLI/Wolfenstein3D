#ifndef WOLF_UI_H
#define WOLF_UI_H

#include "CPlayer.h"
#include <vector>
#include "SDL2/SDL.h"
/* User interface con los datos del jugador*/
class UI {
    CPlayer* activePlayer;
    SDL_Texture* HUD;
    std::vector<SDL_Texture*> numbers, weapons;
    public:
        UI(SDL_Renderer* renderer, CPlayer* activePlayer);
        void draw(SDL_Renderer* renderer);
        void drawNumbers(SDL_Renderer* renderer, int w, int h, std::string toDraw, int padding);
        void drawWeapon(SDL_Renderer* renderer, int w, int h);
        ~UI();
};


#endif //WOLF_UI_H
