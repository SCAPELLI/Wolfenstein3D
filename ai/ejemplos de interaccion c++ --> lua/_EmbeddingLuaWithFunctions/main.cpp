#include <iostream>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

bool succesfulExecution(lua_State* L, int error) {
    if (error != LUA_OK) {
        std::cout<<lua_tostring(L, -1)<<std::endl;
        lua_pop(L, 1);
        return false;
    } else
        return true;
}

//funcion product invocada desde lua, solo recibe el parametro L y retorna la cantidad de elementos cargados en el stack
//los parametros del llamado de la funcion product se cargan en el stack cuando se llama a la funcion desde lua
// se liberan solos.
int product(lua_State* L) {
    float a = lua_tonumber(L, -1);
    float b = lua_tonumber(L, -2);

    std::cout<< "[c++] se ejecuto la funcion product"<<std::endl;
    float c = a * b;
    lua_pushnumber(L, c);

    return 1;
}

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "product", product);

    std::string script = "script.lua";

    if (succesfulExecution(L, luaL_dofile(L, script.c_str()))) {

        lua_getglobal(L, "foo");
        if (lua_isfunction(L, -1) == 1) {

            lua_pushnumber(L, 3);
            lua_pushnumber(L, 3);

            if(succesfulExecution(L, lua_pcall(L, 2, 1, 0))) {
                std::cout << "valor retornado de la funcion foo en c++: " << lua_tonumber(L, -1) << std::endl;
                lua_pop(L, 1);
            }
        }
    }
    lua_close(L);
    return 0;
}
