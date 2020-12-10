#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL_video.h>

//Pre: You must have an SDLContext instantiated at the same scope
class Window {
    SDL_Window* window;
public:
    Window();
    ~Window();
};

#endif
