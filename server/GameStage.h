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
class ChangeWeaponEvent;
#include "PlayerInfo.h"

class GameStage {
    ProtectedEventsQueue& updateEvents;
    std::vector<AbstractEvent*> newEvents;
    std::vector<std::pair<int, std::string>> highScores;
    std::vector< std::string> playersNames; // temporalmente una lista despues en realidad viene de startGame
    Game game;
public:
    explicit GameStage(ProtectedEventsQueue& updateEvents);
    void processEvent(TurnEvent& event);
    void processEvent(MovementEvent& event);
    void processEvent(KillEvent& event);
    void processEvent(ChangeWeaponEvent& event);
    void processEvent(ShootingEvent& event);
    void processEvent(GameOverEvent& event);
    void processEvent(OpenDoorEvent& event);
    void processEvent(SpawnEvent& event);
    void processEvent(int objId,int type, int posX, int posY);
    void pushNewEvents();
    std::vector<PlayerInfo> getPlayersInfo();
    void incrementCooldown();

    };

#endif
