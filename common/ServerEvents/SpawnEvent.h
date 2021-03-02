

#ifndef SPAWNEVENT_H
#define SPAWNEVENT_H
#include "common/include/AbstractEvent.h"
#include "client/include/CGame.h"
#include "common/include/Event.h"

class SpawnEvent : public AbstractEvent {
    updateEventType eventType;
public:
    int id;
    int type;
    int posX;
    int posY;
    SpawnEvent (updateEventType eventType, int id, int type, int posX, int posY);
    void runHandler(CGame& gameStage);
    std::string getSerialization() override;
    updateEventType getEventType();
};

#endif //SPAWNEVENT_H
