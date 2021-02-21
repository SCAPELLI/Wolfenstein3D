#ifndef WOLFENSTEIN3D_RENDERABLE_H
#define WOLFENSTEIN3D_RENDERABLE_H

#include <string>
#include "Vector.h"
#include "SDL2/SDL.h"
#include "Sprite.h"
#include "Camera.h"

class Renderable{
	public:
        Vector position;
        Sprite* sprite;

        Renderable();
        Renderable(const Renderable&) = delete;
        Renderable& operator=(const Renderable&) = delete;
        Renderable(Renderable&& other);
        Renderable& operator=(Renderable&& other);
		Renderable(double x, double y, Sprite* sprite);
		void drawOnScreen(SDL_Renderer*, int posX, int posY, int scale);
		void drawFrom(Camera* origin,
                      std::vector<std::vector<int>>& map,
                      SDL_Renderer* renderer,
                      std::vector<double> &wallDistances);
		~Renderable();
};

#endif