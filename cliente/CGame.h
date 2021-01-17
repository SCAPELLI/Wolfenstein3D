#ifndef WOLFENSTEIN3D_CGAME_H
#define WOLFENSTEIN3D_CGAME_H

#include "GameScreen.h"
#include "CPlayer.h"
#include "Renderable.h"
#include "Wall.h"
#include <map>

class PositionEvent;
class GameOverEvent;
class LifeDecrementEvent;
class ShootingEvent;
class TurnEvent;
class OpenDoorEvent;

class CGame{
	CPlayer activePlayer;
	GameScreen screen;
	std::vector<std::vector<int>> map;
	std::map<int, Renderable*> renderables;
	std::map<int, CPlayer> players;
	std::map<int, Wall> wallSprites;

	public:
		CGame(double x, double y, double fov);
		void draw();
		void rotate(double degrees);
		void spawnRenderable();
		void processEvent(ShootingEvent& event);
        void processEvent(TurnEvent& event);
        void processEvent(GameOverEvent& event);
		void processEvent(LifeDecrementEvent& event);
		void processEvent(PositionEvent& event);
		void processEvent(OpenDoorEvent& event);
		~CGame();
};

#endif