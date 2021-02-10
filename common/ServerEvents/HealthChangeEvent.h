

#ifndef CAMERA_CPP_HEALTHCHANGEEVENT_H
#define CAMERA_CPP_HEALTHCHANGEEVENT_H
#include "../AbstractEvent.h"
#include "Event.h"

class HealthChangeEvent  : public AbstractEvent{

    int health;
    updateEventType eventType;
public:
    HealthChangeEvent (updateEventType eventType, int health);
    updateEventType getEventType();
};


#endif //CAMERA_CPP_HEALTHCHANGEEVENT_H
