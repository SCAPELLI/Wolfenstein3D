cmake_minimum_required(VERSION 3.17)
project(wolfLuaIntegrationExample)

set(CMAKE_CXX_STANDARD 11)

add_executable(wolfLuaIntegrationExample main.cpp Exception.cpp AI.cpp AI.h)

target_link_libraries(wolfLuaIntegrationExample lua)
target_link_libraries(wolfLuaIntegrationExample dl)
