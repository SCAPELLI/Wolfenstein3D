

#ifndef CAMERA_CPP_PICKUPWEAPONEVENT_H
#define CAMERA_CPP_PICKUPWEAPONEVENT_H
#include "../AbstractEvent.h"
#include "Event.h"

class PickUpWeaponEvent  : public AbstractEvent{
    int uniqueId;
    updateEventType eventType;
public:
    PickUpWeaponEvent (updateEventType eventType, int uniqueId);
    updateEventType getEventType();
};


#endif //CAMERA_CPP_PICKUPWEAPONEVENT_H
