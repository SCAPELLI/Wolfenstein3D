

#ifndef CAMERA_CPP_CHANGEWEAPONEVENT_H
#define CAMERA_CPP_CHANGEWEAPONEVENT_H
#include "../AbstractEvent.h"
#include "Event.h"

class ChangeWeaponEvent  : public AbstractEvent{

public:
    int idPlayer;
    int uniqueId; // o tipo???
    updateEventType eventType;
    ChangeWeaponEvent (updateEventType eventType, int idPlayer, int uniqueId);
    updateEventType getEventType();
};


#endif //CAMERA_CPP_CHANGEWEAPONEVENT_H
