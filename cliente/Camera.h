#ifndef WOLFENSTEIN3D_CAMERA_H
#define WOLFENSTEIN3D_CAMERA_H
#include "Vector.h"
#include <vector>
#include <map>
#include "Wall.h"
#include "SDL2/SDL.h"

class Camera{
	Vector cameraPosition;
	Vector planePosition;
	Vector facingPosition;
	int fov;

	public:
		Camera(double x, double y, double fov);
		void moveTo(double x, double y);
		void rotate(double degrees);
		void draw(SDL_Renderer* renderer,
            std::vector<std::vector<int>>& map,
            std::map<int, Wall*>* wallTextures,
            std::vector<double> &wallDistances);
        void resetVision();
		Vector& getPosition();
		Vector& getPlanePosition();
		Vector& getFacingPosition();
		~Camera();
};

#endif