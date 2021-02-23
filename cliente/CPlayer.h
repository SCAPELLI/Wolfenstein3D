#ifndef WOLFENSTEIN3D_CPLAYER_H
#define WOLFENSTEIN3D_CPLAYER_H

#include "Camera.h"
#include "Vector.h"
#include "Renderable.h"
#include "CWeapon.h"
#include "BagOfSprites.h"

class CPlayer{
	Camera camera;
	Vector spawnPoint;
	int hp, lives, ammo, activeWeapon, score;
	std::vector<CWeapon*> weapons;

	public:
        int id;
		CPlayer(double x, double y, double fov, int id);
		void loadWeapons(SDL_Renderer* renderer, BagOfSprites& sprites);
		Camera* getCamera();
		void moveTo(double x, double y);
		void rotate(double degree);
		void drawWeapon(SDL_Renderer* renderer);
		int getActiveWeapon();
		bool shoot();
		int getScore();
		int getLives();
		int getAmmo();
		int getHp();
		void respawn();
		void changeWeapon(int weaponID);
		void increaseScore(int deltaScore);
		void changeAmmo(int deltaAmmo);
		void setHealth(int newHp);
		~CPlayer();
};

#endif