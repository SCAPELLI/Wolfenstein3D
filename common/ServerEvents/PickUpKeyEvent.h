

#ifndef CAMERA_CPP_PICKUPKEYEVENT_H
#define CAMERA_CPP_PICKUPKEYEVENT_H
#include "../AbstractEvent.h"
#include "common/Event.h"

class PickUpKeyEvent  : public AbstractEvent{
public:
    updateEventType eventType;
PickUpKeyEvent (updateEventType eventType);
    updateEventType getEventType();
};


#endif //CAMERA_CPP_PICKUPKEYEVENT_H
