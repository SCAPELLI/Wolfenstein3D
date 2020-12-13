#include "Game.h"

Game::Game(std::vector<std::vector<int>> map, double x, double y, double fov):
	activePlayer(x, y, fov),
	map(std::move(map)){}

Game::~Game(){}