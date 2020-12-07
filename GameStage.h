#ifndef GAMESTAGE_H
#define GAMESTAGE_H
/*
Peligro!
No incluir así:
#include "MovementEvent.h"
#include "TurnEvent.h"
*/


class MovementEvent;
class TurnEvent;

class GameStage {
public:
    void processEvent(TurnEvent& event);
    void processEvent(MovementEvent& event);
};

#endif
