#ifndef WOLFENSTEIN3D_GAME_H
#define WOLFENSTEIN3D_GAME_H

#include "GameScreen.h"
#include "Player.h"
#include <map>

class Game{
	Player activePlayer;
	GameScreen screen;
	std::vector<std::vector<int>> map;
	std::map<int, Renderable> renderables;
	std::map<int, Player> players;

	public:
		Game(double x, double y, double fov);
		void draw();
		//void processEvent(SpawnPlayerEvent& event);
		//void processEvent(SpawnWallEvent& event);
		//void processEvent(SpawnRenderableEvent& event);
		//void processEvent(UpdatePositionEvent& event);
		~Game();
};

#endif