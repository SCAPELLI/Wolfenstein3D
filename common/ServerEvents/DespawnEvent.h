

#ifndef ESPAWNEVENT_H
#define DESPAWNEVENT_H
#include "../server/GameStage.h"
#include "client/CGame.h"
#include "../AbstractEvent.h"
#include "../Event.h"

class DespawnEvent : public AbstractEvent {
public:
    int id;
    int type;
    updateEventType eventType;
    DespawnEvent (updateEventType eventType, int id, int type);
    void runHandler(GameStage& gameStage);
    void runHandler(CGame& renderer);
    updateEventType getEventType();
};

#endif //CAMERA_CPP_DESPAWNEVENT_H
