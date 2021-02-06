

#ifndef ESPAWNEVENT_H
#define DESPAWNEVENT_H
#include "GameStage.h"
#include "../AbstractEvent.h"

class DespawnEvent : public AbstractEvent {
    int id;
    int type;
public:
    DespawnEvent(int id, int type);
    void runHandler(GameStage& gameStage);
};

#endif //CAMERA_CPP_DESPAWNEVENT_H
