

#ifndef CAMERA_CPP_SCORECHANGEEVENT_H
#define CAMERA_CPP_SCORECHANGEEVENT_H
#include "../AbstractEvent.h"
#include "Event.h"

class ScoreChangeEvent  : public AbstractEvent{
public:
    int score;
    updateEventType eventType;
    ScoreChangeEvent (updateEventType eventType, int score);
    updateEventType getEventType();
};


#endif //CAMERA_CPP_SCORECHANGEEVENT_H
