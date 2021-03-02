

#ifndef ESPAWNEVENT_H
#define DESPAWNEVENT_H
#include "server/include/GameStage.h"
#include "client/include/CGame.h"
#include "common/include/AbstractEvent.h"
#include "common/include/Event.h"

class DespawnEvent : public AbstractEvent {
public:
    int id;
    int type;
    updateEventType eventType;
    DespawnEvent (updateEventType eventType, int id, int type);
    void runHandler(GameStage& gameStage);
    void runHandler(CGame& renderer);
    updateEventType getEventType();
    std::string getSerialization();
};

#endif //CAMERA_CPP_DESPAWNEVENT_H
