#ifndef KILLEVENT_H
#define KILLEVENT_H

#include "../AbstractEvent.h"
#include "../Event.h"

class CGame;

class KillEvent: public AbstractEvent {
public:
    updateEventType eventType;
    int idPlayer;
    KillEvent (updateEventType eventType, int idPlayer);
    updateEventType getEventType();
    void runHandler(CGame& renderer) override;
    std::string getSerialization() override;
};

#endif
