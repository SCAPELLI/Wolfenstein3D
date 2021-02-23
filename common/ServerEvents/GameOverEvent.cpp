
#include "GameOverEvent.h"
#include "client/CGame.h"
#include "common/Event.h"
#include "common/EventSerializer.h"


GameOverEvent::GameOverEvent (GameOverEvent& gameOverEvent){}

GameOverEvent::GameOverEvent (updateEventType eventType, int idPlayer) : idPlayer(idPlayer), eventType(eventType){}

void GameOverEvent::runHandler(CGame& game){
    return game.processEvent(*this);
}

updateEventType GameOverEvent::getEventType() {
    return eventType;
}

std::string GameOverEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}
