#ifndef GAME_H_POSITIONEVENT_H
#define GAME_H_POSITIONEVENT_H

#include "AbstractEvent.h"
#include "../cliente/CGame.h"

class PositionEvent : public AbstractEvent {
public:
    int playerId;
    double x,y;
    void runHandler(CGame& game) override;
    std::string getSerialization() override;
    PositionEvent(double x, double y);
    PositionEvent(int playerId, double x, double y);
};


#endif //GAME_H_POSITIONEVENT_H
