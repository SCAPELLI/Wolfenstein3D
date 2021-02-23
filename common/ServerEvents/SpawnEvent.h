

#ifndef SPAWNEVENT_H
#define SPAWNEVENT_H
#include "common/AbstractEvent.h"
#include "client/CGame.h"
#include "common/Event.h"

class SpawnEvent : public AbstractEvent {
    updateEventType eventType;
public:
    int id;
    int type;
    int posX;
    int posY;
    SpawnEvent (updateEventType eventType, int id, int type, int posX, int posY);
    void runHandler(CGame& gameStage);
    updateEventType getEventType();
};

#endif //SPAWNEVENT_H
