

#ifndef CAMERA_CPP_AMMOCHANGEEVENT_H
#define CAMERA_CPP_AMMOCHANGEEVENT_H
#include "../AbstractEvent.h"
#include "../Event.h"

class CGame;

class AmmoChangeEvent  : public AbstractEvent{
    updateEventType eventType;
public:
    int idPlayer;
    int ammo;
    AmmoChangeEvent (updateEventType eventType,int idPlayer, int Ammo);
    void runHandler(CGame& game);
    updateEventType getEventType();
    std::string getSerialization() override;
};


#endif //CAMERA_CPP_AMMOCHANGEEVENT_H
