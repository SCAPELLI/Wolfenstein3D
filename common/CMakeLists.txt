add_library(common
		src/ProtectedEventsQueue.cpp
        ServerEvents/PositionEvent.cpp
		src/AbstractEvent.cpp
        ServerEvents/KillEvent.cpp
		src/QuitEvent.cpp
		src/ShootingEvent.cpp
		src/TurnEvent.cpp
		src/MovementEvent.cpp
        ServerEvents/GameOverEvent.cpp
		src/Event.cpp
		src/OpenDoorEvent.cpp
        ServerEvents/SpawnEvent.cpp
        ServerEvents/DespawnEvent.cpp
        ServerEvents/ChangeWeaponEvent.cpp
        ServerEvents/HealthChangeEvent.cpp
        ServerEvents/AmmoChangeEvent.cpp
        ServerEvents/ScoreChangeEvent.cpp
        ServerEvents/PickUpKeyEvent.cpp
        ServerEvents/PickUpWeaponEvent.cpp
        ServerEvents/DoorOpenedEvent.cpp
		src/EventSerializer.cpp
        ServerEvents/CreateMapEvent.cpp
        ServerEvents/SpawnNotMovableEvent.cpp
		src/BlockingEventsQueue.cpp

		src/Style.cpp
        src/Exception.cpp
        src/IPAddresses.cpp
        src/Socket.cpp
        src/MatchInfo.cpp
        src/Thread.cpp

        ../server/src/GameStage.cpp
		../server/Items/Weapon.cpp
        ../server/src/Player.cpp
        ../server/src/Map.cpp
        ../server/src/GameLoader.cpp
        ../server/src/Game.cpp
        ../server/src/Item.cpp
        ../server/src/CellMap.cpp
		../server/Items/LifeGainItem.cpp
		../server/Items/PointGainItem.cpp
		../server/Items/KeyItem.cpp
		../server/Items/OpenableItem.cpp
		../server/Items/LockedDoor.cpp
		../server/Items/AmmoItem.cpp
        ../server/src/WallRay.cpp
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
		../client/src/ScoreWindow.cpp
		../client/include/ScoreWindow.h
        
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

		../client/src/CGame.cpp
		../client/src/CPlayer.cpp
		../client/src/Camera.cpp
		../client/src/GameScreen.cpp
		../client/src/Ray.cpp
		../client/src/Renderable.cpp
		../client/src/Vector.cpp
		../client/src/Sprite.cpp
		../client/src/Wall.cpp
		../client/src/UI.cpp
		../client/src/AnimatedSprite.cpp
		../client/src/CWeapon.cpp
		../client/src/EnemyPlayer.cpp
		../client/src/BagOfSprites.cpp
		../client/src/SoundManager.cpp
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