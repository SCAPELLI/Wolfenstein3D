add_library(common
        ProtectedEventsQueue.cpp
        ServerEvents/PositionEvent.cpp
        AbstractEvent.cpp
        EventsCatcher.cpp
        ServerEvents/KillEvent.cpp
        QuitEvent.cpp
        ShootingEvent.cpp
        TurnEvent.cpp
        MovementEvent.cpp
        ServerEvents/GameOverEvent.cpp
        Event.cpp
        OpenDoorEvent.cpp
        ServerEvents/SpawnEvent.cpp
        ServerEvents/DespawnEvent.cpp
        ServerEvents/ChangeWeaponEvent.cpp
        ServerEvents/HealthChangeEvent.cpp
        ServerEvents/AmmoChangeEvent.cpp
        ServerEvents/ScoreChangeEvent.cpp
        ServerEvents/PickUpKeyEvent.cpp
        ServerEvents/PickUpWeaponEvent.cpp
        ServerEvents/DoorOpenedEvent.cpp
        EventSerializer.cpp
        ServerEvents/CreateMapEvent.cpp
        ServerEvents/SpawnNotMovableEvent.cpp

        Style.cpp
        src/Exception.cpp
        src/IPAddresses.cpp
        src/Socket.cpp
        src/MatchInfo.cpp
        src/Thread.cpp

        ../server/GameStage.cpp)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

include_directories(${PROJECT_BINARY_DIR})

target_link_libraries(common Qt5::Widgets)

target_link_libraries(common
        yaml-cpp
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES} -lSDL2_ttf pthread)