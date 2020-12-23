#ifndef TURNEVENT_H
#define TURNEVENT_H

#include "AbstractEvent.h"
#include "../server/GameStage.h"
#include "../cliente/CGame.h"

enum TurningSense {ANTICLOCKWISE, CLOCKWISE};

class TurnEvent: public AbstractEvent {
public:
    int player;
    double degrees;
    TurnEvent(int idPlayer, double degrees): player(idPlayer), degrees(degrees) {}
    void runHandler(GameStage& gameStage) override;
    void runHandler(CGame& game);
    double getDegrees();
};

#endif
