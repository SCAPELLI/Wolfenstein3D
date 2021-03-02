#ifndef GAME_H_POSITIONEVENT_H
#define GAME_H_POSITIONEVENT_H

#include "common/include/AbstractEvent.h"
#include "client/include/CGame.h"
#include "server/include/Player.h"
#include "common/include/Event.h"

class PositionEvent : public AbstractEvent {
public:
    int playerId;
    double x,y;
    updateEventType eventType;
    void runHandler(CGame& game) override;
    PositionEvent (updateEventType eventType, int playerId, double x, double y);
    updateEventType getEventType();
    std::string getSerialization() override;
    PositionEvent(double x, double y);
};


#endif //GAME_H_POSITIONEVENT_H
