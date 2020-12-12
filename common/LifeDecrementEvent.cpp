#include "LifeDecrementEvent.h"
#include "Renderer.h"

LifeDecrementEvent::LifeDecrementEvent(int idPlayer, int damage)
    :idPlayer(idPlayer), damage(damage){}

LifeDecrementEvent::LifeDecrementEvent(LifeDecrementEvent& lifeDecrementEvent)
{}

void LifeDecrementEvent::runHandler(Renderer& renderer) {
    renderer.processEvent(*this);
};
