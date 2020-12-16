#include "LifeDecrementEvent.h"
#include "Renderer.h"
#include "../cliente/CGame.h"

LifeDecrementEvent::LifeDecrementEvent(int idPlayer, int damage)
    :idPlayer(idPlayer), damage(damage){}

LifeDecrementEvent::LifeDecrementEvent(LifeDecrementEvent& lifeDecrementEvent)
{}

void LifeDecrementEvent::runHandler(CGame& game) {
    game.processEvent(*this);
};
