#include "AI.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <ProtectedEventsQueue.h>
#include "Exception.h"
#include "../server/PlayerInfo.h"
#include <yaml-cpp/yaml.h>
#include "Event.h"
#include "../common/MovementEvent.h"
#include "../common/TurnEvent.h"
#include "../common/ShootingEvent.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

/*AI::AI(std::vector<std::vector<int>>& map, std::vector<Player>& players, int botId, bool& quit):
        map(map), players(players), botId(botId), quit(quit) {
    L = luaL_newstate();
    luaL_openlibs(L);
    //ruta de yaml, (id del bot siempre 0)
}*/

AI::AI(int levelId): cooldownToAttack(60) {
    L = luaL_newstate();
    luaL_openlibs(L);

    botId = 0;
//    cooldown();
    std::vector<std::vector<int>> map;
    std::string levelPath = std::to_string(levelId) + ".yaml";
    YAML::Node file = YAML::LoadFile("../server/maps/" + levelPath);
    YAML::Node matrixConfig = file["map"];
    for (std::size_t i = 0; i < matrixConfig[0].size(); i++) {
        std::vector<int> fila;
        map.push_back(fila);
        for (std::size_t j = 0; j < matrixConfig.size(); j++) {
            int elem = matrixConfig[j][i].as<int>();
            if (elem < 100 || elem > 300)
                map.back().push_back(0);
            else
                map.back().push_back(1);
        }
    }
    initializeGameContext(map);
}

AI::~AI() {
    lua_close(L);
}

void AI::execute(int error) {
    if (error != LUA_OK) {
        std::string errorMessage = lua_tostring(L, -1);
        lua_pop(L, 1);
        throw Exception(errorMessage);
    }
}

void AI::initializeGameContext(std::vector<std::vector<int>>& map) {
    std::string moduleScript = "../ai/AI.lua";
    execute(luaL_dofile(L, moduleScript.c_str()));

    lua_getglobal(L, "initializeGameContext");
    if (lua_isfunction(L, -1) != 1) throw Exception("Function not found");

    //initializeGameContext first parameter
    lua_newtable(L);
    for (int row = 0; row < map.size(); ++row) {
        lua_newtable(L);
        for (int column = 0; column < map[row].size(); ++column) {
            lua_pushnumber(L, map[row][column]);
            lua_rawseti(L,-2,column+1);
        }
        lua_rawseti(L,-2,row+1);
    }

    //initializeGameContext second parameter
    lua_pushstring(L, std::to_string(botId).c_str());

    execute(lua_pcall(L, 2, 0, 0));
}

int AI::getBotActionId(std::vector<PlayerInfo>& players) {
    lua_getglobal(L, "getBotActionId");
    if (lua_isfunction(L, -1) != 1) throw Exception("Function not found");

    //getBotAction first parameter
    lua_newtable(L);
    for (int i = 0; i < players.size(); ++i) {
        lua_newtable(L);
        lua_newtable(L);
        lua_pushnumber(L, players[i].x);
        lua_setfield(L, -2, "x");
        lua_pushnumber(L, players[i].y);
        lua_setfield(L, -2, "y");
        lua_setfield(L, -2, "position");
        float angle = (float)players[i].angle - (3*PI/2);
        if (angle<0) angle=angle+2*PI;
        lua_pushnumber(L, angle);
        lua_setfield(L, -2, "angle");
        lua_setfield(L, -2, std::to_string(players[i].idPlayer).c_str());
    }

    execute(lua_pcall(L, 1, 1, 0));

    int actionId = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return actionId;
}

void addMovementEventToQueue(ProtectedEventsQueue& events) {
    MovementEvent movementEvent(FORWARD, 0);
    Event event(&movementEvent, MovementEventType);
    events.push(event);
}
void addTurnEventToQueue(ProtectedEventsQueue& events, float sentido) {
    TurnEvent turnEvent(0, PI/180 * sentido);
    Event event(&turnEvent, TurnEventType);
    events.push(event);
}
void addShootingEventToQueue(ProtectedEventsQueue& events) {
    ShootingEvent shootingEvent(0);
    Event event(&shootingEvent, ShootingEventType);
    events.push(event);
}

void AI::generateEvent(ProtectedEventsQueue& events, std::vector<PlayerInfo> players) {
    cooldownToAttack += 1;
    switch (getBotActionId(players)) {
        case MOVE_FOWARD:
            addMovementEventToQueue(events);
            break;
        case TURN_ANTICLOCKWISE:
            addTurnEventToQueue(events, 1);
            break;
        case TURN_CLOCKWISE:
            addTurnEventToQueue(events, -1);
            break;
        case ATTACK:
            if (cooldownToAttack < 60) return;
            addShootingEventToQueue(events);
            cooldownToAttack = 0;
            break;
        case DO_NOTHING:
            std::cout<<"[c++] Do nothing"<<std::endl;
            break;
        default:
            std::cout<<"[c++] Should raise exception"<<std::endl;
            break;
    }
}
