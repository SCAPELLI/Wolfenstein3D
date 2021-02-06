#include "LifeDecrementEvent.h"
#include "Renderer.h"
#include "../cliente/CGame.h"
#include "EventSerializer.h"

LifeDecrementEvent::LifeDecrementEvent(int idPlayer)
    :idPlayer(idPlayer){}

//LifeDecrementEvent::LifeDecrementEvent(LifeDecrementEvent& lifeDecrementEvent) {}

void LifeDecrementEvent::runHandler(CGame& game) {
    game.processEvent(*this);
};

std::string LifeDecrementEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}