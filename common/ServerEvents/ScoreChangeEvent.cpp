

#include "ScoreChangeEvent.h"

ScoreChangeEvent::ScoreChangeEvent (updateEventType eventType, int score)
: score(score), eventType(eventType) {}

updateEventType ScoreChangeEvent::getEventType() {
    return eventType;
}