#include "GameScreen.h"
#include "Player.h"

class Game{
	Player activePlayer;
	GameScreen screen;
	Map map;
	std::vector<Renderable*> renderables;

	public:
		Game(std::vector<std::vector<int>> map, double x, double y, double fov);
		~Game();
}