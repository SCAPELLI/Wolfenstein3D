#include "CGame.h"
#include <string>
#include "common/TurnEvent.h"
#include "ServerEvents/PositionEvent.h"
#include "ServerEvents/DoorOpenedEvent.h"
#include "ServerEvents/SpawnEvent.h"
#include "common/ShootingEvent.h"
#include "ServerEvents/ChangeWeaponEvent.h"
#include "ServerEvents/DespawnEvent.h"
#include "ServerEvents/CreateMapEvent.h"
#include "ServerEvents/SpawnNotMovableEvent.h"

#define PICKUP_SOUND 7


CGame::CGame(double x, double y, double fov):
	activePlayer(x, y, fov, 0),
	screen(&activePlayer, 480, 640),
	map({
  {118,118,118,118,118},
  {118,0,0,0,118},
  {118,0,0,0,118},
  {118,0,0,0,118},
  {118,118,118,118,118}
}), renderables(), players(), soundQueue(){
    activePlayer.loadWeapons(screen.getRenderer());
}

void CGame::draw(){
	screen.draw(map, &renderables, &players);
}

void CGame::rotate(double degrees){
	activePlayer.rotate(degrees);
}

void CGame::processEvent(SpawnNotMovableEvent& event) {
    map[event.posX][event.posY] = event.type;
}

void CGame::processEvent(SpawnEvent& event) {
    if (event.type == 1){
        return; // crear player
    }
    if (event.type == 161) {
        map[event.posY][event.posX] = event.type;
    }
    renderables.emplace(event.id, new Renderable(event.posX, event.posY,std::string("prueba1.bmp"), screen.getRenderer()));
}

void CGame::processEvent(DespawnEvent &event) {
    delete renderables[event.id];
    renderables.erase(event.id);
    soundQueue.push(PICKUP_SOUND, MIX_MAX_VOLUME);
}

//void CGame::processEvent(LifeDecrementEvent& event){}

void CGame::processEvent(ShootingEvent& event){
    int playerID = event.idPlayer;
    if (activePlayer.id == playerID) {
        if (activePlayer.shoot()) soundQueue.push(activePlayer.getActiveWeapon(), MIX_MAX_VOLUME);
    }
//    } else {
//        soundQueue.push(soundEffect);
//    }
}

void CGame::processEvent(GameOverEvent& event){}

//void CGame::processEvent(OpenDoorEvent& event){
//    int doorID = event.getID();
//    Renderable* door = renderables[doorID];
//    door->animate();
//    Vector mapPos = door.position.scale();
//    map[mapPos.y][mapPos.x] = 0;
//}

void CGame::processEvent(ChangeWeaponEvent& event){
    int weaponID = event.type;
    int playerID = event.idPlayer;
    if (playerID == activePlayer.id) {
        activePlayer.changeWeapon(weaponID);
    }
//    } else {
//        players[playerID].changeWeapon(weaponID);
//    }
}

void CGame::processEvent(KillEvent& event){}
void CGame::processEvent(OpenDoorEvent& event){}
void CGame::processEvent(DoorOpenedEvent& event){
    map[event.y][event.x] = 0;
    soundQueue.push(PICKUP_SOUND, MIX_MAX_VOLUME);
}
void CGame::processEvent(CreateMapEvent& event){}

void CGame::advanceTime() {}

void CGame::playSounds() {
    soundQueue.playSounds();
}

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


