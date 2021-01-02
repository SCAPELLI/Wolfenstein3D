#ifndef GAMESTAGE_H
#define GAMESTAGE_H
#include "Game.h"

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
class GameOverEvent;
class GameLoader;
class ShootingEvent;
class OpenDoorEvent;

class GameStage {
    ProtectedEventsQueue& updateEvents;
    Game game;
public:
    explicit GameStage(ProtectedEventsQueue& updateEvents);
    void processEvent(TurnEvent& event);
    void processEvent(MovementEvent& event);
    void processEvent(LifeDecrementEvent& event);
    void processEvent(ShootingEvent& event);
    void processEvent(GameOverEvent& event);
    void processEvent(OpenDoorEvent& event);
};

#endif
