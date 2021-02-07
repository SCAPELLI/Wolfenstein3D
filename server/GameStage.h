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
class KillEvent;
class GameOverEvent;
class GameLoader;
class ShootingEvent;
class OpenDoorEvent;
class SpawnEvent;

class GameStage {
    ProtectedEventsQueue& updateEvents;
    std::vector<AbstractEvent*> newEvents;
    Game game;
public:
    explicit GameStage(ProtectedEventsQueue& updateEvents);
    void processEvent(TurnEvent& event);
    void processEvent(MovementEvent& event);
    void processEvent(KillEvent& event);
    void processEvent(ShootingEvent& event);
    void processEvent(GameOverEvent& event);
    void processEvent(OpenDoorEvent& event);
    void processEvent(SpawnEvent& event);
    void processEvent(int objId,int type, int posX, int posY);
    void IncrementCooldown();

    };

#endif
