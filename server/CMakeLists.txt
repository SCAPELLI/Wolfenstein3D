add_executable(server
	GameStage.cpp
    Items/Weapon.cpp
    Player.cpp
    Map.cpp
    GameLoader.cpp
    Game.cpp
    Item.cpp
	CellMap.cpp
	Items/LifeGainItem.cpp
    Items/PointGainItem.cpp
    Items/KeyItem.cpp
    Items/OpenableItem.cpp
    Items/LockedDoor.cpp
    Items/AmmoItem.cpp
	WallRay.cpp
	Items/Rocket.cpp
	ai/AI.cpp

	src/main.cpp
    src/TCPServer.cpp
	src/Match.cpp
	src/ProtectedLobby.cpp
	src/CommunicationChannelServer.cpp
	src/AcceptNewUsersThread.cpp
	src/UserThread.cpp)

target_link_libraries(server common)

target_link_libraries(server lua)

target_link_libraries(server dl)

target_link_libraries(server 
	yaml-cpp 
	${SDL2_LIBRARY} 
	${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES}
	${SDL2_TTF_LIBRARIES} -lSDL2_ttf pthread)

target_link_libraries(server  
	${YAML_CPP_LIBRARIES})