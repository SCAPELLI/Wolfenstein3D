

#ifndef CAMERA_CPP_HEALTHCHANGEEVENT_H
#define CAMERA_CPP_HEALTHCHANGEEVENT_H
#include "../AbstractEvent.h"
#include "Event.h"

class HealthChangeEvent  : public AbstractEvent{
    updateEventType eventType;
public:
    int health;
    HealthChangeEvent (updateEventType eventType, int health);
    updateEventType getEventType();
    void runHandler(CGame &game);
};


#endif //CAMERA_CPP_HEALTHCHANGEEVENT_H
