#include "client/CGame.h"
#include "ScoreChangeEvent.h"

ScoreChangeEvent::ScoreChangeEvent (updateEventType eventType, int idPlayer, int score)
:  eventType(eventType),idPlayer(idPlayer),score(score) {}

updateEventType ScoreChangeEvent::getEventType() {
    return eventType;
}

void ScoreChangeEvent::runHandler(CGame &game) {
    game.processEvent(*this);
}