#ifndef COLADEEVENTOS_KillEvent_H
#define COLADEEVENTOS_KillEvent_H

#include "../AbstractEvent.h"

class CGame;

class KillEvent: public AbstractEvent {
public:
    int idPlayer;
    KillEvent(int idPlayer);
    KillEvent(KillEvent& KillEvent);
    void runHandler(CGame& renderer) override;
};

#endif
