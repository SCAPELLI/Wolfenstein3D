

#ifndef SPAWNEVENT_H
#define SPAWNEVENT_H
#include "../AbstractEvent.h"
#include "Event.h"

class SpawnEvent : public AbstractEvent {
    int id;
    int type;
    int posX;
    int posY;
    updateEventType eventType;
public:
    SpawnEvent (updateEventType eventType, int id, int type, int posX, int posY);
    void runHandler(GameStage& gameStage);
    updateEventType getEventType();
};


#endif //SPAWNEVENT_H
