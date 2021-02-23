

#ifndef CAMERA_CPP_PICKUPWEAPONEVENT_H
#define CAMERA_CPP_PICKUPWEAPONEVENT_H
#include "../AbstractEvent.h"
#include "../Event.h"

class PickUpWeaponEvent  : public AbstractEvent{
    updateEventType eventType;
public:
    int idPlayer;
    int uniqueId;
    PickUpWeaponEvent (updateEventType eventType, int idPlayer, int uniqueId);
    updateEventType getEventType();
    std::string getSerialization() override;
};


#endif //CAMERA_CPP_PICKUPWEAPONEVENT_H
