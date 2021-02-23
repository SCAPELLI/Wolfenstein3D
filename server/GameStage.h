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
class BlockingEventsQueue;
class Event;
#include "PlayerInfo.h"

class GameStage {
    std::vector<std::pair<int, std::string>> highScores;
    int levelId;
    std::vector<BlockingEventsQueue>& queues;
//    std::vector< std::string> playersNames; // temporalmente una lista despues en realidad viene de startGame
    Game game;
    std::vector<AbstractEvent*> newEvents;
public:
    explicit GameStage(std::vector<BlockingEventsQueue>& queues,
                       std::map<int, std::string>& playersNames, int levelId);
    void processEvent(TurnEvent& event);
    void processEvent(MovementEvent& event);
    void processEvent(ChangeWeaponEvent& event);
    void processEvent(ShootingEvent& event);
    void processEvent(OpenDoorEvent& event);
    void processEvent(int objId,int type, int posX, int posY);
    void insertInAllQueuesEvent(Event& event);
    void pushNewEvents();
    std::vector<PlayerInfo> getPlayersInfo();
    void incrementCooldown();

    };

#endif
