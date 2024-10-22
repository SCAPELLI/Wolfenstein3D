

#ifndef CAMERA_CPP_HEALTHCHANGEEVENT_H
#define CAMERA_CPP_HEALTHCHANGEEVENT_H
#include "common/include/AbstractEvent.h"
#include "common/include/Event.h"

class HealthChangeEvent  : public AbstractEvent{
    updateEventType eventType;
public:
    int idPlayer;
    int health;
    HealthChangeEvent (updateEventType eventType, int idPlayer, int health);
    updateEventType getEventType();
    std::string getSerialization() override;
    void runHandler(CGame &game);
};


#endif //CAMERA_CPP_HEALTHCHANGEEVENT_H
