

#include "ChangeWeaponEvent.h"
#include "Event.h"
#include "cliente/CGame.h"
#include "server/GameStage.h"


ChangeWeaponEvent::ChangeWeaponEvent (int idPlayer, int type)
: idPlayer(idPlayer), type(type){}

void ChangeWeaponEvent::runHandler(CGame &renderer) {
    renderer.processEvent(*this);
}

void ChangeWeaponEvent::runHandler(GameStage &game) {
    game.processEvent(*this);
}