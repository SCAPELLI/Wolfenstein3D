#include "Window.h"
#include "Exception.h"
#include <string>

//Pre: You must have an SDLContext instantiated at the same scope
Window::Window() {
    window = SDL_CreateWindow( "El mejor tp del mundo",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               640, 480, SDL_WINDOW_SHOWN );
    if(window == nullptr) {
        throw Exception(
                "SDL window creation failed with error:"
                + std::string(SDL_GetError()));
    }
}

Window::~Window() {
    SDL_DestroyWindow(window);
}
