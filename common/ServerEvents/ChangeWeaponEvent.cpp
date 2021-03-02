

#include "ChangeWeaponEvent.h"
#include "common/include/Event.h"
#include "client/include/CGame.h"
#include "server/include/GameStage.h"
#include "common/include/EventSerializer.h"


ChangeWeaponEvent::ChangeWeaponEvent (int idPlayer, int type)
: idPlayer(idPlayer), type(type){}

void ChangeWeaponEvent::runHandler(CGame &renderer) {
    renderer.processEvent(*this);
}

void ChangeWeaponEvent::runHandler(GameStage &game) {
    game.processEvent(*this);
}

std::string ChangeWeaponEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}