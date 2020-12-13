#ifndef WOLFENSTEIN3D_PLAYER_H
#define WOLFENSTEIN3D_PLAYER_H

#include "Camera.h"
#include "Vector.h"

class Player{
	Camera camera;
	Vector spawnPoint;
	int hp;
	int lifes;
	int id;

	public:
		Player(double x, double y, double fov, int id);
		Camera* getCamera();
		void move(double x, double y);
		void rotate(double degree);
		void shoot();
		void respawn();
		void decreaseLife(int damage);
		~Player();
};

#endif