#include <iostream>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

bool succesfulExecution(lua_State* lua, int error) {
    if (error != LUA_OK) {
        std::cout<<lua_tostring(lua, -1)<<std::endl;
        return false;
    } else
        return true;
}

int main() {
    lua_State *lua = luaL_newstate();
    luaL_openlibs(lua);

    std::string script = "script.lua";
    std::string script2 = "script2.lua";

    if (succesfulExecution(lua, luaL_dofile(lua, script.c_str()))) {

        //puedo ejecutar dos scripts distintos y lua lo interpreta como el mismo programa
        //observar que en script2 el valor  de "a" ya està inicilizado por el script 1
        luaL_dofile(lua, script2.c_str());

        //Pedir un entero inicializado en lua
        lua_getglobal(lua, "a");
        if (lua_isnumber(lua, -1) == 1) {
            auto a = (float) lua_tonumber(lua, -1);
            std::cout<< a <<std::endl;
        }

        //Pedir un script inicializado en lua
        lua_getglobal(lua, "unNombre");
        if (lua_isstring(lua, -1) == 1) {
        	std::string nombre = lua_tostring(lua, -1);
        	std::cout<< nombre <<std::endl;
        }

        //Pedir elementos de una tabla inicializada en lua
        lua_getglobal(lua, "diccionario");
        if (lua_istable(lua, -1)) {
        	lua_pushstring(lua, "key1");
        	lua_gettable(lua, -2);
        	std::string key1 = lua_tostring(lua, -1);
        	lua_pop(lua, 1);
        	std::cout<< key1 <<std::endl;

        	lua_pushstring(lua, "key2");
        	lua_gettable(lua, -2);
        	std::string key2 = lua_tostring(lua, -1);
        	lua_pop(lua, 1);
        	std::cout<< key2 <<std::endl;

        	lua_pushstring(lua, "key3");
        	lua_gettable(lua, -2);
        	int key3 = lua_tonumber(lua, -1);
        	lua_pop(lua, 1);
        	std::cout<< key3 <<std::endl;
        }
    }
    lua_close(lua);
    return 0;
}
