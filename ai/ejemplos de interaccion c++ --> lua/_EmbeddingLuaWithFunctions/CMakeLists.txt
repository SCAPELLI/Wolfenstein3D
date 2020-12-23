cmake_minimum_required(VERSION 3.17)
project(EmbendingLua)

set(CMAKE_CXX_STANDARD 11)

add_executable(EmbendingLua main.cpp)

target_link_libraries(EmbendingLua lua)
target_link_libraries(EmbendingLua dl)