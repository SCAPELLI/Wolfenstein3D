#include <SDL2/SDL.h>
#include <string>
#include "SDLContext.h"
#include "Exception.h"

SDLContext::SDLContext() {
    int i = SDL_Init( SDL_INIT_VIDEO );
    if (i < 0) {
        throw Exception(
                "SDL initialization failed with error: "
                + std::string(SDL_GetError()));
    }
}
SDLContext::~SDLContext(){
    SDL_Quit();
}
