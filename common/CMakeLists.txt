add_library(common
        ProtectedEventsQueue.cpp
        ServerEvents/PositionEvent.cpp
        AbstractEvent.cpp
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
		BlockingEventsQueue.cpp

        Style.cpp
        src/Exception.cpp
        src/IPAddresses.cpp
        src/Socket.cpp
        src/MatchInfo.cpp
        src/Thread.cpp

        ../server/GameStage.cpp
        ../server/Items/Weapon.cpp
    ../server/Player.cpp
    ../server/Map.cpp
    ../server/GameLoader.cpp
    ../server/Game.cpp
    ../server/Item.cpp
        ../server/CellMap.cpp
        ../server/Items/LifeGainItem.cpp
    ../server/Items/PointGainItem.cpp
    ../server/Items/KeyItem.cpp
    ../server/Items/OpenableItem.cpp
    ../server/Items/LockedDoor.cpp
    ../server/Items/AmmoItem.cpp
        ../server/WallRay.cpp
        ../server/Items/Rocket.cpp
        ../server/ai/AI.cpp
		../server/src/SenderThread.cpp
		../server/src/ReceiverThread.cpp

        
    ../server/src/TCPServer.cpp
        ../server/src/Match.cpp
        ../server/src/ProtectedLobby.cpp
        ../server/src/CommunicationChannelServer.cpp
        ../server/src/AcceptNewUsersThread.cpp
        ../server/src/UserThread.cpp

		../client/src/main.cpp
        ../client/src/MenuScreen.cpp
        ../client/src/ScreenManager.cpp
        ../client/include/ScreenManager.h
        ../client/src/StartScreen.cpp
        ../client/include/StartScreen.h
        ../client/src/NicknameScreen.cpp
        ../client/include/NicknameScreen.h
        ../client/src/GamesScreen.cpp
        ../client/include/GamesScreen.h
        
        ../client/src/DataTable.cpp
        ../client/include/DataTable.h 

        ../client/src/InfoScreen.cpp
        ../client/include/InfoScreen.h

        ../client/src/Client.cpp

        ../client/src/WaitingRoomScreen.cpp
        ../client/include/WaitingRoomScreen.h

        ../client/src/NewMatchScreen.cpp
        ../client/include/NewMatchScreen.h

		../client/src/CommunicationChannelClient.cpp
        ../client/src/TCPClient.cpp

	../client/CGame.cpp
        ../client/CPlayer.cpp
        ../client/Camera.cpp
        ../client/GameScreen.cpp
        ../client/Ray.cpp
        ../client/Renderable.cpp
        ../client/Vector.cpp
        ../client/Sprite.cpp
        ../client/Wall.cpp 
        ../client/UI.cpp
        ../client/AnimatedSprite.cpp
        ../client/CWeapon.cpp
        ../client/EnemyPlayer.cpp
        ../client/BagOfSprites.cpp
        ../client/SoundManager.cpp
        src/Message.cpp include/Message.h ServerEvents/StartEvent.cpp ServerEvents/StartEvent.h
		src/Protocol.cpp)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

include_directories(${PROJECT_BINARY_DIR})

target_link_libraries(common Qt5::Widgets)

target_link_libraries(common
        yaml-cpp SDL2
		SDL2_mixer	SDL2_image
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES} -lSDL2_ttf pthread)