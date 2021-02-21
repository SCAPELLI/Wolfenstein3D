#ifndef AI_H
#define AI_H


const float PI = 3.14159265358979323846;
const int MOVE_FOWARD = 1;
const int TURN_ANTICLOCKWISE = 2;
const int TURN_CLOCKWISE = 3;
const int ATTACK = 4;
const int DO_NOTHING = 5;

////////////////////////////////////////////////////////////////////////
//"class Player" se borrará en la integración con server
/*class Player {
public:
    float x;
    float y;
    float angle;

    int lifeNumber;

    Player(float x, float y, float angle): x(x), y(y), angle(angle) {}
};*/
////////////////////////////////////////////////////////////////////////

#include <vector>

class lua_State;
class ProtectedEventsQueue;
class PlayerInfo;

class AI {
    int botId;
    lua_State* L;
public:
    //AI(std::vector<std::vector<int>>& map, std::vector<Player>& players, int botId, bool& quit);
    explicit AI(int levelId);
    ~AI();
    void execute(int error);
    void initializeGameContext(std::vector<std::vector<int>>& map);
    int getBotActionId(std::vector<PlayerInfo>& players);
    void generateEvent(ProtectedEventsQueue& events, std::vector<PlayerInfo> players);
};

#endif
