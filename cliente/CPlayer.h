#ifndef WOLFENSTEIN3D_CPLAYER_H
#define WOLFENSTEIN3D_CPLAYER_H

#include "Camera.h"
#include "Vector.h"
#include "Renderable.h"
#include "CWeapon.h"

class CPlayer{
	Camera camera;
	Vector spawnPoint;
	int hp, lives, ammo, activeWeapon;
	std::vector<CWeapon*> weapons;

	public:
        int id;
		CPlayer(double x, double y, double fov, int id);
		void loadWeapons(SDL_Renderer* renderer);
		Camera* getCamera();
		void moveTo(double x, double y);
		void rotate(double degree);
		void drawWeapon(SDL_Renderer* renderer);
		void shoot();
		void respawn();
		void changeWeapon(int weaponID);
		void decreaseLife(int damage);
		~CPlayer();
};

#endif