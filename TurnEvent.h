#ifndef TURNEVENT_H
#define TURNEVENT_H

#include "AbstractEvent.h"
#include "GameStage.h"

enum TurningSense {ANTICLOCKWISE, CLOCKWISE};

class TurnEvent: public AbstractEvent {
    TurningSense sense;
    double degrees;
public:
    explicit TurnEvent(TurningSense sense, double degrees): sense(sense), degrees(degrees) {}
    void runHandler(GameStage& gameStage) override;
    TurningSense getSense();
    double getDegrees();
};

#endif
