#include "AI.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <common/include/ProtectedEventsQueue.h>
#include "../common/include/Exception.h"
#include "server/include/PlayerInfo.h"
#include <yaml-cpp/yaml.h>
#include <algorithm>
#include "common/include/Event.h"
#include "common/include/MovementEvent.h"
#include "common/include/TurnEvent.h"
#include "common/include/EventSerializer.h"
#include "common/include/ShootingEvent.h"
#include "../../common/include/Message.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

const int COOLDOWN = 6;

AI::AI(int levelId, int botId): botId(botId), cooldown(0) {
    L = luaL_newstate();
    luaL_openlibs(L);

    std::vector<std::vector<int>> map;
    std::string levelPath = std::to_string(levelId) + ".yaml";
    YAML::Node file = YAML::LoadFile("../../server/maps/" + levelPath);
    YAML::Node matrixConfig = file["map"];
    for (std::size_t i = 0; i < matrixConfig[0].size(); i++) {
        std::vector<int> fila;
        map.push_back(fila);
        for (std::size_t j = 0; j < matrixConfig.size(); j++) {
            int elem = matrixConfig[j][i].as<int>();
            if (elem < 100 || elem >= 300 || elem == 116 || elem == 117 || elem == 109 || elem == 108 || elem == 125 || elem == 124 || elem == 161 || elem == 158 )
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
    std::string moduleScript = "../../server/ai/AI.lua";
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
        lua_pushnumber(L, players[i].life);
        lua_setfield(L, -2, "life");
        lua_setfield(L, -2, std::to_string(players[i].idPlayer).c_str());
    }

    execute(lua_pcall(L, 1, 1, 0));

    int actionId = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return actionId;
}

void AI::addMovementEventToQueue(ProtectedEventsQueue& events, MovementDirection direction) {
    if (cooldown < COOLDOWN) {
        ++cooldown;
        return;
    }
    cooldown = 0;
    MovementEvent movementEvent(direction, 0);
    Event event(&movementEvent, MovementEventType);
    Message msg(EventSerializer::serialize(event));
    events.push(msg);
}
void AI::addTurnEventToQueue(ProtectedEventsQueue& events, float sense) {
    TurnEvent turnEvent(0, PI/250 * sense);
    Event event(&turnEvent, TurnEventType);
    Message msg(EventSerializer::serialize(event));
    events.push(msg);
}
void AI::addShootingEventToQueue(ProtectedEventsQueue& events) {
    if (cooldown < 2) {
        ++cooldown;
        return;
    }
    cooldown = 0;
    ShootingEvent shootingEvent(0);
    Event event(&shootingEvent, ShootingEventType);
    Message msg(EventSerializer::serialize(event));
    events.push(msg);
}

bool AI::botIsDead(std::vector<PlayerInfo>* players) {
    auto it = std::find_if(
            players->begin(), players->end(),
            [&] (const PlayerInfo& player) { return player.idPlayer == botId;});
    //return (it->life<=0);
    return (it->isGameOver);
}

void AI::generateEvent(ProtectedEventsQueue& events, std::vector<PlayerInfo> players) {
    if (botIsDead(&players)) {

        return;
    }
    switch (getBotActionId(players)) {
        case MOVE_FOWARD:
            addMovementEventToQueue(events, FORWARD);
            break;
        case TURN_ANTICLOCKWISE:
            addTurnEventToQueue(events, 1);
            break;
        case TURN_CLOCKWISE:
            addTurnEventToQueue(events, -1);
            break;
        case ATTACK:
            addShootingEventToQueue(events);
            break;
        case MOVE_BACKWARD:
            addMovementEventToQueue(events, BACKWARD);
            break;
        default:
            break;
    }
}
