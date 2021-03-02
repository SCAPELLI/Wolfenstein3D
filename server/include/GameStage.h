#ifndef GAMESTAGE_H
#define GAMESTAGE_H

#include <common/include/QuitEvent.h>
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
/* Clase que interactúa entre el lobby y el game*/
class GameStage {
    std::vector<std::pair<int, std::string>> highScores;
    int levelId;
    std::vector<BlockingEventsQueue>* queues; // ojo que las colas no son referencias pero el vector si, quizas
//    std::vector< std::string> playersNames; // temporalmente una lista despues en realidad viene de startGame
    Game game;
    std::vector<AbstractEvent*> newEvents;
public:
    GameStage(std::vector<BlockingEventsQueue>* queues,
                       std::map<int, std::string>& playersNames, int levelId, char* configPath);
    void processEvent(TurnEvent& event);
    void processEvent(MovementEvent& event);
    void processEvent(ChangeWeaponEvent& event);
    void processEvent(ShootingEvent& event);
    void processEvent(OpenDoorEvent& event);
    void processEvent(QuitEvent& event);
    void pushNewEvents();
    std::vector<PlayerInfo> getPlayersInfo();
    void incrementCooldown();

    void ifSomeoneWinNotifyHim();
    bool gameFinished();
    };

#endif
