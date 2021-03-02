qt5_wrap_ui(UIS_HEADERS
        ui/MenuWindow.ui
        ui/NewMapWindow.ui
        ui/EditorScreen.ui
        ui/ScreenManager.ui
        ui/NewMapDialog.ui)

add_executable(Editor ${UIS_HEADERS} 
        src/main.cpp src/MenuWindow.cpp include/MenuWindow.h src/NewMapWindow.cpp include/NewMapWindow.h src/ScreenManager.cpp include/ScreenManager.h src/EditorScreen.cpp include/EditorScreen.h src/TextureList.cpp include/TextureList.h src/Tile.cpp include/Tile.h include/Tilemap.h src/Prueba.cpp include/Prueba.h src/Coordinate.cpp include/Coordinate.h src/TilemapScene.cpp include/TilemapScene.h src/Texture.cpp include/Texture.h src/Mode.cpp include/Mode.h src/DrawMode.cpp include/DrawMode.h src/EraseMode.cpp include/EraseMode.h src/SpriteFileManager.cpp include/SpriteFileManager.h src/SpriteTabs.cpp include/SpriteTabs.h src/NewMapDialog.cpp include/NewMapDialog.h ../common/src/Style.cpp ../common/include/Style.h)