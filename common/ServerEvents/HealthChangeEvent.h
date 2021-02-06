

#ifndef CAMERA_CPP_HEALTHCHANGEEVENT_H
#define CAMERA_CPP_HEALTHCHANGEEVENT_H
#include "../AbstractEvent.h"

class HealthChangeEvent  : public AbstractEvent{

    int health;
public:
    HealthChangeEvent(int health);
};


#endif //CAMERA_CPP_HEALTHCHANGEEVENT_H
