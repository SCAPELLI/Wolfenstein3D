cmake_minimum_required(VERSION 3.17)
project(Wolfenstein)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 ")

#Incluyo el root para no andar haciendo "../blah/"

######################################################
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(yaml-cpp)
INCLUDE(FindPkgConfig)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${YAML_CPP_INCLUDE_DIRS})

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
######################################################

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(common)
add_subdirectory(client)
#add_subdirectory(server)
#add_subdirectory(editor)