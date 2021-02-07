

#ifndef ESPAWNEVENT_H
#define DESPAWNEVENT_H
#include "GameStage.h"
#include "../AbstractEvent.h"
#include "Event.h"

class DespawnEvent : public AbstractEvent {
    int id;
    int type;
    updateEventType eventType;
public:
    DespawnEvent (updateEventType eventType, int id, int type);
    void runHandler(GameStage& gameStage);
    updateEventType getEventType();
};

#endif //CAMERA_CPP_DESPAWNEVENT_H
