#include "CGame.h"
#include <string>
#include <iostream>
#include "../common/PositionEvent.h"
#include "../common/TurnEvent.h"


CGame::CGame(double x, double y, double fov):
	activePlayer(x, y, fov, 0),
	screen(activePlayer.getCamera(), 640, 480),
	map({
  {114,115,116,117,114},
  {114,3,0,2,118},
  {114,0,0,0,119},
  {114,0,0,0,120},
  {114,114,114,114,114}
}), renderables(), players(){}

void CGame::draw(){
	screen.draw(map, &renderables, &players);
}

void CGame::rotate(double degrees){
	activePlayer.rotate(degrees);
}

void CGame::spawnRenderable(){
	//renderables.emplace(1, new Renderable(230/2, 100/2, std::string("prueba.bmp"), screen.getRenderer()));
	renderables.emplace(2, new Renderable(32, 32, std::string("prueba.bmp"), screen.getRenderer()));
}

void CGame::processEvent(LifeDecrementEvent& event){}
void CGame::processEvent(ShootingEvent& event){}
void CGame::processEvent(GameOverEvent& event){}
void CGame::processEvent(OpenDoorEvent& event){}
void CGame::processEvent(TurnEvent& event) {
    this->activePlayer.rotate(event.getDegrees());
}
void CGame::processEvent(PositionEvent& event){
    this->activePlayer.moveTo(event.x, event.y);
}

CGame::~CGame(){
    std::map<int, Renderable*>::iterator it;
    for (it = renderables.begin(); it != renderables.end(); ++it){
        delete it->second;
    }
}