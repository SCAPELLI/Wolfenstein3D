add_executable(server
	src/main.cpp
		)


PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

include_directories(${PROJECT_BINARY_DIR})

target_link_libraries(server common)

target_link_libraries(server
		yaml-cpp
		${SDL2_LIBRARY}
		${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES}
		${SDL2_TTF_LIBRARIES} -lSDL2_ttf pthread)

target_link_libraries(server
		${YAML_CPP_LIBRARIES})

target_link_libraries(server Qt5::Widgets)
target_link_libraries(server lua)
target_link_libraries(server dl)
