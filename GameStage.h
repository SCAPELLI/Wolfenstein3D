#ifndef GAMESTAGE_H
#define GAMESTAGE_H

/*
Peligro!
No incluir así:
#include "MovementEvent.h"
#include "TurnEvent.h"
*/

class ProtectedEventsQueue;
class MovementEvent;
class TurnEvent;

class GameStage {
    ProtectedEventsQueue& updateEvents;
public:
    explicit GameStage(ProtectedEventsQueue& updateEvents):
            updateEvents(updateEvents) {}
    void processEvent(TurnEvent& event);
    void processEvent(MovementEvent& event);
};

#endif
