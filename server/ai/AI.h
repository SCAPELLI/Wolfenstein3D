#ifndef AI_H
#define AI_H


const float PI = 3.14159265358979323846;
const int MOVE_BACKWARD = 0;
const int MOVE_FOWARD = 1;
const int TURN_ANTICLOCKWISE = 2;
const int TURN_CLOCKWISE = 3;
const int ATTACK = 4;

#include <vector>
#include <common/include/MovementEvent.h>

class lua_State;
class ProtectedEventsQueue;
class PlayerInfo;

class AI {
    int botId;
    lua_State* L;
    int cooldown;
public:
    AI(int levelId, int botId);
    ~AI();
    void execute(int error);
    void initializeGameContext(std::vector<std::vector<int>>& map);
    int getBotActionId(std::vector<PlayerInfo>& players);
    void generateEvent(ProtectedEventsQueue& events, std::vector<PlayerInfo> players);
    bool botIsDead(std::vector<PlayerInfo>* players);
    void addShootingEventToQueue(ProtectedEventsQueue& events);
    void addTurnEventToQueue(ProtectedEventsQueue& events, float sense);
    void addMovementEventToQueue(ProtectedEventsQueue& events, MovementDirection direction);
};

#endif
