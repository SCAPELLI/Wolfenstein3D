#ifndef GAME_H_POSITIONEVENT_H
#define GAME_H_POSITIONEVENT_H

#include "../AbstractEvent.h"
#include "cliente/CGame.h"
#include "Player.h"

class PositionEvent : public AbstractEvent {
    int playerId;
public:
    double x,y;
    void runHandler(CGame& game) override;
    PositionEvent(int playerId, double x, double y);
};


#endif //GAME_H_POSITIONEVENT_H
