#ifndef TURNEVENT_H
#define TURNEVENT_H

#include "AbstractEvent.h"
#include "GameStage.h"

enum TurningSense {ANTICLOCKWISE, CLOCKWISE};

class TurnEvent: public AbstractEvent {
    TurningSense sense;
public:
    explicit TurnEvent(TurningSense sense): sense(sense) {}
    void runHandler(GameStage& gameStage) override;
};

#endif
