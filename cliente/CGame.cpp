#include "CGame.h"
#include <string>
#include "../common/PositionEvent.h"
#include "../common/TurnEvent.h"


CGame::CGame(double x, double y, double fov):
	activePlayer(x, y, fov, 0),
	screen(&activePlayer, 480, 640),
	map({
  {114,114,114,114,114},
  {114,0,0,0,114},
  {114,0,0,0,114},
  {114,0,0,0,114},
  {114,114,114,114,114}
}), renderables(), players(){
    activePlayer.loadWeapons(screen.getRenderer());
}

void CGame::draw(){
	screen.draw(map, &renderables, &players);
}

void CGame::rotate(double degrees){
	activePlayer.rotate(degrees);
}

void CGame::spawnRenderable(){
	renderables.emplace(2, new Renderable(65, 66, std::string("prueba.bmp"), screen.getRenderer()));
}

void CGame::processEvent(LifeDecrementEvent& event){}

//void CGame::processEvent(ShootingEvent& event){
//    int playerID = event.getID();
//    if (activePlayer.id == playerID){
//        activePlayer.shoot();
//    } else {
//        soundQueue.push(soundEffect);
//    }
//}

void CGame::processEvent(GameOverEvent& event){}

//void CGame::processEvent(OpenDoorEvent& event){
//    int doorID = event.getID();
//    Renderable* door = renderables[doorID];
//    door->animate();
//    Vector mapPos = door.position.scale();
//    map[mapPos.y][mapPos.x] = 0;
//}

//void CGame::processEvent(ChangeWeaponEvent& event){
//    int weaponID = event.getWeaponID();
//    int playerID = event.getPlayerID();
//    players[playerID].changeWeapon(weaponID);
//}

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

void CGame::processEvent(ShootingEvent &event) {}

void CGame::processEvent(OpenDoorEvent &event) {}
