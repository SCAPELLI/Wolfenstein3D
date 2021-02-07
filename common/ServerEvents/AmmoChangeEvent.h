

#ifndef CAMERA_CPP_AMMOCHANGEEVENT_H
#define CAMERA_CPP_AMMOCHANGEEVENT_H
#include "../AbstractEvent.h"
#include "Event.h"

class AmmoChangeEvent  : public AbstractEvent{
    updateEventType eventType;
    int ammo;
public:
    AmmoChangeEvent (updateEventType eventType, int Ammo);
    updateEventType getEventType();
};


#endif //CAMERA_CPP_AMMOCHANGEEVENT_H
