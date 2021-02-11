#include "UI.h"
#include <SDL_image.h>
#define ROUTE "../cliente/sprites/hud_elements/"
#define FILE_EXTENSION ".png"
#include <string>

UI::UI(SDL_Renderer* renderer, CPlayer *activePlayer): activePlayer(activePlayer){
    this->HUD = IMG_LoadTexture(renderer, (std::string(ROUTE) + "HUD" + std::string(FILE_EXTENSION)).c_str());
    for (int i = 0; i < 10; i++){
        this->numbers.push_back(IMG_LoadTexture(renderer,
                           (std::string(ROUTE) + std::to_string(i) + std::string(FILE_EXTENSION)).c_str()));
    }
}

void UI::draw(SDL_Renderer* renderer){
    int w,h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    SDL_Rect dest = {0, h - 64, w, 64};
    SDL_RenderCopy(renderer, this->HUD, NULL, &dest);
    //activePlayer->drawWeapon(renderer);
}

UI::~UI(){
    SDL_DestroyTexture(HUD);
    for (int i = 0; i < 10; i++){
        SDL_DestroyTexture(numbers[i]);
    }
}
