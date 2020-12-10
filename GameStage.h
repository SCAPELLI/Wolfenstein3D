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
class LifeDecrementEvent;
class Game;

class GameStage {
    Game& game;
    ProtectedEventsQueue& updateEvents;
public:
    explicit GameStage(ProtectedEventsQueue& updateEvents, Game& game):
            updateEvents(updateEvents), game(game) {}
    void processEvent(TurnEvent& event);
    void processEvent(MovementEvent& event);
    void processEvent(LifeDecrementEvent& event);
};

#endif
