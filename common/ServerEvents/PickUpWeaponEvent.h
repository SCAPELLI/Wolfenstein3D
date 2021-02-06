

#ifndef CAMERA_CPP_PICKUPWEAPONEVENT_H
#define CAMERA_CPP_PICKUPWEAPONEVENT_H
#include "../AbstractEvent.h"

class PickUpWeaponEvent  : public AbstractEvent{
    int uniqueId;
public:
    PickUpWeaponEvent(int uniqueId);
};


#endif //CAMERA_CPP_PICKUPWEAPONEVENT_H
