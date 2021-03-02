#ifndef WOLF_WALL_H
#define WOLF_WALL_H

#include "SDL2/SDL.h"
/*Clase que representa una pared del mapa*/
class Wall{
    SDL_Texture* texture;
    public:
        Wall(int id, SDL_Renderer* renderer);
        void drawLine(SDL_Renderer* renderer, int xPixel, int columnValue, int drawStart, int height);
        ~Wall();
};

#endif //WOLF_WALL_H
