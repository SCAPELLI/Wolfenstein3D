#include "client/include/CGame.h"
#include "ScoreChangeEvent.h"
#include "common/include/EventSerializer.h"

ScoreChangeEvent::ScoreChangeEvent (updateEventType eventType, int idPlayer, int score)
:  eventType(eventType),idPlayer(idPlayer),score(score) {}

updateEventType ScoreChangeEvent::getEventType() {
    return eventType;
}

void ScoreChangeEvent::runHandler(CGame &game) {
    game.processEvent(*this);
}

std::string ScoreChangeEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}