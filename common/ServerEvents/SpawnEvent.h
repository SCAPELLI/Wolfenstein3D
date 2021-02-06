

#ifndef SPAWNEVENT_H
#define SPAWNEVENT_H
#include "../AbstractEvent.h"

class SpawnEvent : public AbstractEvent {
    int id;
    int type;
    int posX;
    int posY;
public:
    SpawnEvent(int id, int type, int posX, int posY);
    void runHandler(GameStage& gameStage);
};


#endif //SPAWNEVENT_H
