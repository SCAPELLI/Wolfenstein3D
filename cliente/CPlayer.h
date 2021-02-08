#ifndef WOLFENSTEIN3D_CPLAYER_H
#define WOLFENSTEIN3D_CPLAYER_H

#include "Camera.h"
#include "Vector.h"

class CPlayer{
	Camera camera;
	Vector spawnPoint;
	int hp;
	int lives;
	int id;

	public:
		CPlayer(double x, double y, double fov, int id);
		Camera* getCamera();
		void moveTo(double x, double y);
		void rotate(double degree);
		void shoot();
		void respawn();
		void decreaseLife(int damage);
		~CPlayer();
};

#endif