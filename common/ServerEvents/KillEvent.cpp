#include "ServerEvents/KillEvent.h"
#include "Renderer.h"
#include "cliente/CGame.h"

KillEvent::KillEvent(int idPlayer) //kill
    :idPlayer(idPlayer){}

KillEvent::KillEvent(KillEvent& KillEvent)
{}

void KillEvent::runHandler(CGame& game) {
    game.processEvent(*this);
};
