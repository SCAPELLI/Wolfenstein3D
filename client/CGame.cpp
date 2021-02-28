#include "CGame.h"
#include <string>
#include <utility>
#include "common/TurnEvent.h"
#include "../common/ServerEvents/PositionEvent.h"
#include "../common/ServerEvents/DoorOpenedEvent.h"
#include "../common/ServerEvents/SpawnEvent.h"
#include "common/ShootingEvent.h"
#include "../common/ServerEvents/ChangeWeaponEvent.h"
#include "../common/ServerEvents/DespawnEvent.h"
#include "../common/ServerEvents/CreateMapEvent.h"
#include "../common/ServerEvents/SpawnNotMovableEvent.h"
#include "../common/ServerEvents/ScoreChangeEvent.h"
#include "../common/ServerEvents/AmmoChangeEvent.h"
#include "../common/ServerEvents/HealthChangeEvent.h"
#include "../common/ServerEvents/GameOverEvent.h"
#include "../common/ServerEvents/KillEvent.h"
#include "../common/ServerEvents/PickUpKeyEvent.h"

#define PICKUP_SOUND 7


CGame::CGame(double x, double y, double fov, std::vector<std::vector<int>> map, int playerId, bool& isPlaying):
	activePlayer(x, y, fov, playerId),
	screen(&activePlayer, 480, 640),
	map(std::move(map)), renderables(), players(), soundQueue(), sprites(screen.getRenderer()),
	isPlaying(isPlaying){
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
    players[playerId] = new EnemyPlayer(screen.getRenderer(), playerId, spawnPoint, sprites);
}

void CGame::processEvent(SpawnEvent& event) {
    if (event.type == 161 || event.type == 160) {
        map[event.posY][event.posX] = event.type;
    }
    renderables[event.id] =  Renderable(event.posY, event.posX, &sprites.items[event.type]);
}
void CGame::processEvent(HealthChangeEvent& event) {
    if (event.idPlayer != activePlayer.id) return;
    activePlayer.setHealth(event.health);
}

void CGame::processEvent(PickUpKeyEvent& event) {
    if (event.idPlayer != activePlayer.id) return;
    activePlayer.hasKey = true;
}

void CGame::processEvent(DespawnEvent &event) {
    renderables.erase(event.id);
    soundQueue.push(PICKUP_SOUND, MIX_MAX_VOLUME);
}


void CGame::processEvent(ShootingEvent& event){
    int playerID = event.idPlayer;
    if (activePlayer.id == playerID) {
        if (activePlayer.shoot()) soundQueue.push(activePlayer.getActiveWeapon(), MIX_MAX_VOLUME/10);
    } else {
        int distance = activePlayer.getPosition().distance(players[event.idPlayer]->position);
        soundQueue.push(players[event.idPlayer]->getActiveWeapon(), MIX_MAX_VOLUME/10 - distance/20);
    }
}

void CGame::processEvent(GameOverEvent& event){
    if (event.idPlayer != activePlayer.id) return; //players[event.idPlayer].despawn();
    isPlaying = false;
}

void CGame::processEvent(ChangeWeaponEvent& event){
    int weaponID = event.type;
    int playerID = event.idPlayer;
    if (playerID == activePlayer.id) {
        activePlayer.changeWeapon(weaponID);
    } else {
        players[playerID]->changeWeapon(weaponID);
    }
}

void CGame::processEvent(ScoreChangeEvent& event){
    //if (event.idPlayer != activePlayer.id) return;
    activePlayer.increaseScore(event.score);
}

void CGame::processEvent(KillEvent& event){
    if (event.idPlayer != activePlayer.id) {
        players[event.idPlayer]->die();
        return;
    }
    activePlayer.respawn();
}


void CGame::processEvent(DoorOpenedEvent& event){
    map[event.y][event.x] = 0;
    soundQueue.push(PICKUP_SOUND, MIX_MAX_VOLUME);
}

void CGame::processEvent(CreateMapEvent& event){}

void CGame::processEvent(AmmoChangeEvent& event){
    if (event.idPlayer != activePlayer.id) return;
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

    if (event.playerId != activePlayer.id) {
        players[event.playerId]->walkTo(Vector(event.x, event.y));
    } else {
        this->activePlayer.moveTo(event.x, event.y);
    }
}

CGame::~CGame(){
    std::map<int, EnemyPlayer*>::iterator itp;
    for (itp = players.begin(); itp != players.end(); ++itp){
        delete itp->second;
    }
}


