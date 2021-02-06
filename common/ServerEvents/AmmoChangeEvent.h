

#ifndef CAMERA_CPP_AMMOCHANGEEVENT_H
#define CAMERA_CPP_AMMOCHANGEEVENT_H
#include "../AbstractEvent.h"

class AmmoChangeEvent  : public AbstractEvent{
    int ammo;
public:
    AmmoChangeEvent(int Ammo);

};


#endif //CAMERA_CPP_AMMOCHANGEEVENT_H
