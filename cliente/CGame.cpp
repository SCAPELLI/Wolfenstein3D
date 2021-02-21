#include "CGame.h"
#include <string>
#include <utility>
#include "common/TurnEvent.h"
#include "ServerEvents/PositionEvent.h"
#include "ServerEvents/DoorOpenedEvent.h"
#include "ServerEvents/SpawnEvent.h"
#include "common/ShootingEvent.h"
#include "ServerEvents/ChangeWeaponEvent.h"
#include "ServerEvents/DespawnEvent.h"
#include "ServerEvents/CreateMapEvent.h"
#include "ServerEvents/SpawnNotMovableEvent.h"
#include "ServerEvents/ScoreChangeEvent.h"
#include "ServerEvents/AmmoChangeEvent.h"
#include "ServerEvents/HealthChangeEvent.h"
#include "ServerEvents/GameOverEvent.h"

#define PICKUP_SOUND 7


CGame::CGame(double x, double y, double fov, std::vector<std::vector<int>> map):
	activePlayer(x, y, fov, 0),
	screen(&activePlayer, 480, 640),
	map(std::move(map)), renderables(), players(), soundQueue(), sprites(screen.getRenderer()){
        activePlayer.loadWeapons(screen.getRenderer(), sprites);
}

void CGame::draw(){
	screen.draw(map, renderables, players);
}

void CGame::rotate(double degrees){
	activePlayer.rotate(degrees);
}

void CGame::processEvent(SpawnNotMovableEvent& event) {
    map[event.posX][event.posY] = event.type;
}

void CGame::spawnEnemy(int playerId, Vector spawnPoint){
    players[playerId] = new EnemyPlayer(screen.getRenderer(), -1, spawnPoint, sprites);
}

void CGame::processEvent(SpawnEvent& event) {
    if (event.type == 1){
        players[event.id] = new EnemyPlayer(screen.getRenderer(), event.id, Vector(event.posY, event.posX), sprites); // crear player
    }
    if (event.type == 161) {
        map[event.posY][event.posX] = event.type;
    }
    renderables[event.id] =  Renderable(event.posX, event.posY, &sprites.items[event.type]);
}
void CGame::processEvent(HealthChangeEvent& event) {
    //if (event.idPlayer != activePlayer.id) return;
    activePlayer.setHealth(event.health);
}


void CGame::processEvent(DespawnEvent &event) {
    renderables.erase(event.id);
    soundQueue.push(PICKUP_SOUND, MIX_MAX_VOLUME);
}


void CGame::processEvent(ShootingEvent& event){
    int playerID = event.idPlayer;
    if (activePlayer.id == playerID) {
        if (activePlayer.shoot()) soundQueue.push(activePlayer.getActiveWeapon(), MIX_MAX_VOLUME);
    }
//    } else {
//        soundQueue.push(soundEffect);
//    }
}

void CGame::processEvent(GameOverEvent& event){
    //if (event.idPlayer != activePlayer.id) players[event.idPlayer].despawn();
    // mostrar top
}

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

void CGame::processEvent(ScoreChangeEvent& event){
    //if (event.idPlayer != activePlayer.id) return;
    activePlayer.increaseScore(event.score);
}

void CGame::processEvent(KillEvent& event){
    //if (event.idPlayer != activePlayer.id) return; // players[event.idPlayer].kill();
    activePlayer.respawn();
}


void CGame::processEvent(DoorOpenedEvent& event){
    map[event.y][event.x] = 0;
    soundQueue.push(PICKUP_SOUND, MIX_MAX_VOLUME);
}

void CGame::processEvent(CreateMapEvent& event){}

void CGame::processEvent(AmmoChangeEvent& event){
    //if (event.idPlayer != activePlayer.id) return;
    activePlayer.changeAmmo(event.ammo);
}

void CGame::advanceTime() {}

void CGame::playSounds() {
    soundQueue.playSounds();
}

void CGame::processEvent(TurnEvent& event) {
    if (event.idPlayer != activePlayer.id) return;
    this->activePlayer.rotate(event.getDegrees());
}
void CGame::processEvent(PositionEvent& event){
    //if (event.idPlayer != activePlayer.id) return; // players[event.idPlayer].moveTo(event.x, event.y)
    this->activePlayer.moveTo(event.x, event.y);
}

CGame::~CGame(){
    std::map<int, EnemyPlayer*>::iterator itp;
    for (itp = players.begin(); itp != players.end(); ++itp){
        delete itp->second;
    }
}

