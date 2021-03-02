
#include "GameOverEvent.h"
#include "client/include/CGame.h"
#include "common/include/Event.h"
#include "common/include/EventSerializer.h"


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
