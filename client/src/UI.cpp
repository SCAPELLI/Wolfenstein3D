#include "client/include/UI.h"
#include <SDL_image.h>
#define ROUTE "../../client/sprites/hud_elements/"
#define FILE_EXTENSION ".png"
#include <string>
#define NUMBER_SIZE 16
#define WEAPON_SIZE 128
#define NUMBER_HEIGHT 30
#define WEAPON_HEIGHT 40
#define WEAPON_PADDING 54
#define NUMBER_PADDING 40
#define CHAR_TO_INT 48
#define SCORE_LAYOUT 116
#define LIFE_LAYOUT SCORE_LAYOUT+80
#define FACE_LAYOUT LIFE_LAYOUT+16
#define HEALTH_LAYOUT LIFE_LAYOUT+160
#define AMMO_LAYOUT HEALTH_LAYOUT+96
#define KEY_LAYOUT AMMO_LAYOUT+16
#define WEAPON_LAYOUT AMMO_LAYOUT+48
#define AMOUNT_OF_WEAPONS 5

UI::UI(SDL_Renderer* renderer, CPlayer *activePlayer): activePlayer(activePlayer){
    this->HUD = IMG_LoadTexture(renderer, (std::string(ROUTE) + "HUD" + std::string(FILE_EXTENSION)).c_str());
    this->key = IMG_LoadTexture(renderer, (std::string(ROUTE) + "k1" + std::string(FILE_EXTENSION)).c_str());
    for (int i = 0; i < 10; i++){
        this->numbers.push_back(IMG_LoadTexture(renderer,
                           (std::string(ROUTE) + std::to_string(i) + std::string(FILE_EXTENSION)).c_str()));
        this->faces.push_back(IMG_LoadTexture(renderer, (std::string(ROUTE) + std::string("f") +
                                std::to_string(i) + std::string(FILE_EXTENSION)).c_str()));
    }
    for (int i = 0; i < AMOUNT_OF_WEAPONS; i++){
        this->weapons.push_back(IMG_LoadTexture(renderer,
                                                (std::string(ROUTE) + std::string("w") + std::to_string(i) + std::string(FILE_EXTENSION)).c_str()));
    }
}

void UI::draw(SDL_Renderer* renderer){
    int w,h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    SDL_Rect dest = {0, h - 64, w, 64};
    SDL_RenderCopy(renderer, this->HUD, NULL, &dest);
    drawNumbers(renderer, w, h - NUMBER_PADDING, std::to_string(activePlayer->getScore()), SCORE_LAYOUT);
    drawNumbers(renderer, w, h - NUMBER_PADDING, std::to_string(activePlayer->getLives()), LIFE_LAYOUT);
    drawNumbers(renderer, w, h - NUMBER_PADDING, std::to_string(activePlayer->getHp()), HEALTH_LAYOUT);
    drawNumbers(renderer, w, h - NUMBER_PADDING, std::to_string(activePlayer->getAmmo()), AMMO_LAYOUT);
    drawFace(renderer, FACE_LAYOUT, h - 62);
    drawKey(renderer, KEY_LAYOUT, h - 64);
    drawWeapon(renderer, WEAPON_LAYOUT, h - WEAPON_PADDING);
}

void UI::drawFace(SDL_Renderer* renderer, int w, int h){
    int toDrawId = (activePlayer->getHp() / 10) - 1;
    if (toDrawId < 0) toDrawId = 0;
    SDL_Rect dest = {w, h, 76, 60};
    SDL_RenderCopy(renderer, this->faces[toDrawId], NULL, &dest);
}

void UI::drawKey(SDL_Renderer* renderer, int w, int h){
    if (!activePlayer->hasKey) return;
    SDL_Rect dest = {w, h, 64, 64};
    SDL_RenderCopy(renderer, key, NULL, &dest);
}

void UI::drawNumbers(SDL_Renderer* renderer, int w, int h, std::string toDraw, int padding){
    for (int i = toDraw.size() - 1; i >= 0; i--){
        int xPixel = padding - (toDraw.size() - i) * NUMBER_SIZE;
        SDL_Rect dest = {xPixel, h, NUMBER_SIZE, NUMBER_HEIGHT};
        int numberToDraw = toDraw[i] - CHAR_TO_INT;
        SDL_Texture* toDraw = this->numbers[numberToDraw];
        SDL_RenderCopy(renderer, toDraw, NULL, &dest);
    }
}

void UI::drawWeapon(SDL_Renderer* renderer, int w, int h){
    SDL_Rect dest = {w, h, WEAPON_SIZE, WEAPON_HEIGHT};
    SDL_RenderCopy(renderer, this->weapons[activePlayer->getActiveWeapon()], NULL, &dest);
}

UI::~UI(){
    SDL_DestroyTexture(HUD);
    SDL_DestroyTexture(key);
    for (int i = 0; i < 10; i++){
        SDL_DestroyTexture(numbers[i]);
        SDL_DestroyTexture(faces[i]);
    }
}
