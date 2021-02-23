
#include "GameOverEvent.h"
#include "client/CGame.h"
#include "../Event.h"
#include "../EventSerializer.h"


GameOverEvent::GameOverEvent (updateEventType eventType, int idPlayer,
                              std::map<std::string, std::vector<int>>& names)
              : idPlayer(idPlayer), eventType(eventType), highscores(names){}

void GameOverEvent::runHandler(CGame& game){
    return game.processEvent(*this);
}

updateEventType GameOverEvent::getEventType() {
    return eventType;
}

std::string GameOverEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}
