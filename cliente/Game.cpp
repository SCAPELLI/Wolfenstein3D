#include "Game.h"

Game::Game(double x, double y, double fov):
	activePlayer(x, y, fov, 0),
	screen(activePlayer.getCamera(), 640, 480),
	map(), renderables(), players(){}

void Game::draw(){
	screen.draw(map, &renderables, &players);
}

//void Game::processEvent(SpawnPlayerEvent& event){}
//void Game::processEvent(SpawnWallEvent& event){}
//void Game::processEvent(SpawnRenderableEvent& event){}
//void Game::processEvent(UpdatePositionEvent& event){}

Game::~Game(){}