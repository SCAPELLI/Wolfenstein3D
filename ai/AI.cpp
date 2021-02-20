#include "AI.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <ProtectedEventsQueue.h>
#include "Exception.h"
#include "../server/PlayerInfo.h"
#include <yaml-cpp/yaml.h>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

/*AI::AI(std::vector<std::vector<int>>& map, std::vector<Player>& players, int botId, bool& quit):
        map(map), players(players), botId(botId), quit(quit) {
    L = luaL_newstate();
    luaL_openlibs(L);
    //ruta de yaml, (id del bot siempre 0)
}*/

AI::AI(int levelId) {
    L = luaL_newstate();
    luaL_openlibs(L);

    botId = 0;

    std::vector<std::vector<int>> map;
    std::string levelPath = std::to_string(levelId) + ".yaml";
    YAML::Node file = YAML::LoadFile("../server/maps/" + levelPath);

    YAML::Node matrixConfig = file["map"];
    for (std::size_t i = 0; i < matrixConfig.size(); i++) {
        for (std::size_t j = 0; j < matrixConfig[i].size(); j++) {
            int elem = matrixConfig[i][j].as<int>();
            if (elem < 100 || elem > 300)
                map.at(i).at(j) = 0;
            else
                map.at(i).at(j) = 1;
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
    std::string moduleScript = "../AI.lua";
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
        lua_pushnumber(L, players[i].angle);
        lua_setfield(L, -2, "angle");
        lua_setfield(L, -2, std::to_string(players[i].idPlayer).c_str());
    }

    execute(lua_pcall(L, 1, 1, 0));

    int actionId = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return actionId;
}

void AI::generateEvent(ProtectedEventsQueue& events, std::vector<PlayerInfo> players) {

    switch (getBotActionId(players)) {
        case MOVE_FOWARD:
            std::cout<<"[c++] Foward"<<std::endl;
            break;
        case TURN_ANTICLOCKWISE:
            std::cout<<"[c++] Turn anticlockwise"<<std::endl;
            break;
        case TURN_CLOCKWISE:
            std::cout<<"[c++] Turn clockwise"<<std::endl;
            break;
        case ATTACK:
            std::cout<<"[c++] Attack"<<std::endl;
            break;
        case DO_NOTHING:
            std::cout<<"[c++] Do nothing"<<std::endl;
            break;
        default:
            std::cout<<"[c++] Should raise exception"<<std::endl;
            break;
    }
}
