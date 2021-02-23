qt5_wrap_ui(UIS_HEADERS
        ui/MenuScreen.ui
        ui/ScreenManager.ui
        ui/StartScreen.ui
        ui/NicknameScreen.ui
        ui/GamesScreen.ui
        ui/NewMatchScreen.ui
        ui/InfoScreen.ui
        ui/WaitingRoomScreen.ui
		ui/ScoreWindow.ui)

add_executable(client
	${UIS_HEADERS} 
        src/main.cpp
        )


PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

include_directories(${PROJECT_BINARY_DIR})

target_link_libraries(client common)

target_link_libraries(client Qt5::Widgets)

target_link_libraries(client 
	yaml-cpp 
	${SDL2_LIBRARY} 
	${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES}
	${SDL2_TTF_LIBRARIES} -lSDL2_ttf pthread)

target_link_libraries(client lua)
target_link_libraries(client dl)