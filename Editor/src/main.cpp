#include <iostream>
#include <QtWidgets/QApplication>
#include <MenuWindow.h>
#include <NewMapWindow.h>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <ScreenManager.h>
#include <EditorScreen.h>
#include <Coordinate.h>

int main(int argc, char *argv[]) {
    /*
    QApplication app(argc, argv);
    MenuWindow menu;
    menu.show();
    return app.exec();
     */


    QApplication app(argc, argv);
    ScreenManager screenManager;
    screenManager.show();
    return app.exec();


    /*
    std::map<Coordinate, Tile*> map;
    Coordinate a(1, 31);
    Coordinate b(50, 10);
    map.insert(std::pair<Coordinate, Tile*>(a, new Tile()));
    if (map.find(b) != map.end()) {
        std::cout << "uwu";
    } else {
        std::cout << "owo";
    }
    for (auto i = map.begin(); i != map.end(); i++) {
        Tile* tile = std::move(i->second);
        map.erase(i->first);
        delete tile;
    }
     */

    /*
    Coordinate a(1, 31);
    Coordinate b(4, 10);
    std::map<Coordinate, Tile> map;
    Tile tile("uwu");
    map.insert(std::pair<Coordinate, Tile>(a, tile));
     */
}
