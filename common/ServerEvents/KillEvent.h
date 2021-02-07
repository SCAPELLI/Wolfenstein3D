#ifndef KILLEVENT_H
#define KILLEVENT_H

#include "../AbstractEvent.h"
#include "Event.h"

class CGame;

class KillEvent: public AbstractEvent {
public:
    int idPlayer;
    updateEventType eventType;
    KillEvent (updateEventType eventType, int idPlayer);
    KillEvent ( KillEvent& KillEvent);
    updateEventType getEventType();
    void runHandler(CGame& renderer) override;
};

#endif
