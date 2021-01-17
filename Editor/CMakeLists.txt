cmake_minimum_required(VERSION 3.17)
project(Editor)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(yaml-cpp)

message("[INFO] La raiz del proyecto es ${PROJECT_SOURCE_DIR}")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${YAML_CPP_INCLUDE_DIRS})

qt5_wrap_ui(UIS_HEADERS
        ui/MenuWindow.ui
        ui/NewMapWindow.ui
        ui/EditorScreen.ui
        ui/ScreenManager.ui)

message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

message("Headers generados: ${UIS_HEADERS}")

set(CMAKE_CXX_STANDARD 11)

add_executable(Editor ${UIS_HEADERS} src/main.cpp src/MenuWindow.cpp include/MenuWindow.h src/NewMapWindow.cpp include/NewMapWindow.h src/ScreenManager.cpp include/ScreenManager.h src/EditorScreen.cpp include/EditorScreen.h src/TextureList.cpp include/TextureList.h src/Tile.cpp include/Tile.h src/Tilemap.cpp include/Tilemap.h src/Prueba.cpp include/Prueba.h src/Coordinate.cpp include/Coordinate.h src/TilemapScene.cpp include/TilemapScene.h src/Texture.cpp include/Texture.h src/Mode.cpp include/Mode.h src/DrawMode.cpp include/DrawMode.h src/EraseMode.cpp include/EraseMode.h src/SpriteFileManager.cpp include/SpriteFileManager.h src/SpriteTabs.cpp include/SpriteTabs.h)

target_link_libraries(Editor Qt5::Widgets ${YAML_CPP_LIBRARIES})
