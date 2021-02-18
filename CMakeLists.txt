cmake_minimum_required(VERSION 3.17)
project(Wolf)


set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")


include_directories(${PROJECT_SOURCE_DIR}/server)
include_directories(${PROJECT_SOURCE_DIR}/common)
include_directories(${PROJECT_SOURCE_DIR})


set(SERVER_SOURCE_FILES
        server/GameStage.cpp

        server/main.cpp

        common/Exception.cpp
        common/ProtectedEventsQueue.cpp

        common/SDLContext.cpp

        common/ServerEvents/PositionEvent.cpp
        common/AbstractEvent.cpp
        common/EventsCatcher.cpp
        common/ServerEvents/KillEvent.cpp
        common/QuitEvent.cpp
        common/ShootingEvent.cpp
        common/TurnEvent.cpp
        common/MovementEvent.cpp
        common/ServerEvents/GameOverEvent.cpp
        common/Event.cpp
        common/Window.cpp

        server/Server.cpp
        server/Weapon.cpp
        server/Player.cpp
        server/Map.cpp
        server/GameLoader.cpp
        #        server/Knife.cpp
        #        server/Gun.cpp
        server/Game.cpp
        cliente/CGame.cpp
        cliente/CPlayer.cpp
        cliente/Camera.cpp
        cliente/GameScreen.cpp
        cliente/Ray.cpp
        cliente/Renderable.cpp
        cliente/Vector.cpp
        cliente/Sprite.cpp

        common/OpenDoorEvent.cpp
        common/Item.cpp common/Item.h common/CellMap.cpp common/CellMap.h cliente/Wall.h cliente/Wall.cpp common/Items/LifeGainItem.cpp common/Items/LifeGainItem.h common/Items/PointGainItem.cpp common/Items/PointGainItem.h common/Items/KeyItem.cpp common/Items/KeyItem.h common/Items/OpenableItem.cpp common/Items/OpenableItem.h common/Items/LockedDoor.cpp common/Items/LockedDoor.h common/Items/AmmoItem.cpp common/Items/AmmoItem.h common/ServerEvents/SpawnEvent.cpp common/ServerEvents/SpawnEvent.h common/ServerEvents/DespawnEvent.cpp common/ServerEvents/DespawnEvent.h common/ServerEvents/ChangeWeaponEvent.cpp common/ServerEvents/ChangeWeaponEvent.h common/ServerEvents/HealthChangeEvent.cpp common/ServerEvents/HealthChangeEvent.h common/ServerEvents/AmmoChangeEvent.cpp common/ServerEvents/AmmoChangeEvent.h common/ServerEvents/ScoreChangeEvent.cpp common/ServerEvents/ScoreChangeEvent.h common/ServerEvents/PickUpKeyEvent.cpp common/ServerEvents/PickUpKeyEvent.h common/ServerEvents/PickUpWeaponEvent.cpp common/ServerEvents/PickUpWeaponEvent.h common/ServerEvents/DoorOpenedEvent.cpp common/ServerEvents/DoorOpenedEvent.h common/Constants.h
        cliente/UI.cpp cliente/UI.h cliente/AnimatedSprite.cpp cliente/AnimatedSprite.h
        common/Items/AmmoItem.h cliente/CWeapon.cpp cliente/CWeapon.h
        common/WallRay.cpp common/WallRay.h
        common/EventSerializer.cpp common/EventSerializer.h common/ServerEvents/CreateMapEvent.cpp common/ServerEvents/CreateMapEvent.h common/ServerEvents/SpawnNotMovableEvent.cpp common/ServerEvents/SpawnNotMovableEvent.h cliente/SoundManager.cpp cliente/SoundManager.h  common/Items/Rocket.cpp common/Items/Rocket.h)
        
        


add_executable(Wolf server/main.cpp ${SERVER_SOURCE_FILES})


find_package(yaml-cpp)
INCLUDE(FindPkgConfig)

message("[INFO] La raiz del proyecto es ${PROJECT_SOURCE_DIR}")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${YAML_CPP_INCLUDE_DIRS})


PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} PkgConfig::SDL2_Mixer)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

message("Headers generados: ${SERVER_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 11)

target_link_libraries(Wolf yaml-cpp ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES} -lSDL2_ttf pthread)
target_link_libraries(Wolf  ${YAML_CPP_LIBRARIES})