#ifndef AI_H
#define AI_H

#include <vector>

const float PI = 3.14159265358979323846;
const int MOVE_FOWARD = 1;
const int TURN_ANTICLOCKWISE = 2;
const int TURN_CLOCKWISE = 3;
const int ATTACK = 4;
const int DO_NOTHING = 5;

////////////////////////////////////////////////////////////////////////
//"class Player" se borrará en la integración con server
class Player {
public:
    float x;
    float y;
    float angle;
    Player(float x, float y, float angle): x(x), y(y), angle(angle) {}
};
////////////////////////////////////////////////////////////////////////

class lua_State;

class AI {
    std::vector<std::vector<int>>& map;
    std::vector<Player>& players;
    int botId;
    lua_State* L;
    bool& quit;
public:
    AI(std::vector<std::vector<int>>& map, std::vector<Player>& players, int botId, bool& quit);
    ~AI();
    void execute(int error);
    void initializeGameContext();
    int getBotActionId();
    void operator()();
};

#endif
