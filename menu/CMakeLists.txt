cmake_minimum_required(VERSION 3.17)
project(menu)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

message("[INFO] La raiz del proyecto es ${PROJECT_SOURCE_DIR}")

include_directories(${PROJECT_SOURCE_DIR}/include)
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

qt5_wrap_ui(UIS_HEADERS
        ui/MenuScreen.ui
        ui/ScreenManager.ui
        ui/StartScreen.ui
        ui/NicknameScreen.ui)

message("Headers generados: ${UIS_HEADERS}")

add_executable(menu ${UIS_HEADERS} src/main.cpp src/MenuScreen.cpp include/MenuScreen.h src/ScreenManager.cpp include/ScreenManager.h src/StartScreen.cpp include/StartScreen.h ../common/Style.cpp ../common/Style.h src/NicknameScreen.cpp include/NicknameScreen.h)

target_link_libraries(menu Qt5::Widgets)