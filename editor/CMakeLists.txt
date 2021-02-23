qt5_wrap_ui(UIS_HEADERS
        ui/MenuWindow.ui
        ui/NewMapWindow.ui
        ui/EditorScreen.ui
        ui/ScreenManager.ui
        ui/NewMapDialog.ui)

add_executable(Editor ${UIS_HEADERS} 
        src/main.cpp 
        src/MenuWindow.cpp 
        src/NewMapWindow.cpp  
        src/ScreenManager.cpp 
        src/EditorScreen.cpp 
        src/TextureList.cpp 
        src/Tile.cpp  
        src/Prueba.cpp 
        src/Coordinate.cpp
        src/TilemapScene.cpp 
        src/Texture.cpp
        src/Mode.cpp
        src/DrawMode.cpp 
        src/EraseMode.cpp 
        src/SpriteFileManager.cpp
        src/SpriteTabs.cpp 
        src/NewMapDialog.cpp 
        ../common/Style.cpp)