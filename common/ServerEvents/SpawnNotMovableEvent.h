

#ifndef CAMERA_CPP_SPAWNNOTMOVABLEEVENT_H
#define CAMERA_CPP_SPAWNNOTMOVABLEEVENT_H
#include "common/include/AbstractEvent.h"

class SpawnNotMovableEvent : public AbstractEvent {
    updateEventType eventType;
public:
    int type;
    int posX;
    int posY;
    SpawnNotMovableEvent (updateEventType eventType, int type, int posX, int posY);
    void runHandler(CGame& gameStage);
    std::string getSerialization() override;
    updateEventType getEventType();
};


#endif //CAMERA_CPP_SPAWNNOTMOVABLEEVENT_H
