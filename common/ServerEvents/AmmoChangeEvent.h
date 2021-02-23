

#ifndef CAMERA_CPP_AMMOCHANGEEVENT_H
#define CAMERA_CPP_AMMOCHANGEEVENT_H
#include "../AbstractEvent.h"
#include "common/Event.h"

class CGame;

class AmmoChangeEvent  : public AbstractEvent{
    updateEventType eventType;
public:
    int ammo;
    AmmoChangeEvent (updateEventType eventType, int Ammo);
    void runHandler(CGame& game);
    updateEventType getEventType();
};


#endif //CAMERA_CPP_AMMOCHANGEEVENT_H
