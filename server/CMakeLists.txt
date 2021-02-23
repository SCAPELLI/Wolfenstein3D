add_executable(server
	src/main.cpp
    )
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

target_link_libraries(server Qt5::Widgets)