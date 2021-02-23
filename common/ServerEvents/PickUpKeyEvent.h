

#ifndef CAMERA_CPP_PICKUPKEYEVENT_H
#define CAMERA_CPP_PICKUPKEYEVENT_H
#include "../AbstractEvent.h"
#include "../Event.h"

class PickUpKeyEvent  : public AbstractEvent{
public:
    updateEventType eventType;
    int idPlayer;
    PickUpKeyEvent (updateEventType eventType, int idPlayer);
    updateEventType getEventType();
};


#endif //CAMERA_CPP_PICKUPKEYEVENT_H
