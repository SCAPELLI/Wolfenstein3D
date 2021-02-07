#ifndef GAME_H_POSITIONEVENT_H
#define GAME_H_POSITIONEVENT_H

#include "../AbstractEvent.h"
#include "cliente/CGame.h"
#include "Player.h"
#include "Event.h"

class PositionEvent : public AbstractEvent {
    int playerId;
public:
    double x,y;
    updateEventType eventType;
    void runHandler(CGame& game) override;
    PositionEvent (updateEventType eventType, int playerId, double x, double y);
    updateEventType getEventType();
};


#endif //GAME_H_POSITIONEVENT_H
