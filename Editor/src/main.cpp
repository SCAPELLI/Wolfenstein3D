#include <iostream>
#include <QtWidgets/QApplication>
#include <MenuWindow.h>
#include <NewMapWindow.h>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <ScreenManager.h>
#include <EditorScreen.h>
#include <Coordinate.h>
#include "SpriteFileManager.h"

int main(int argc, char *argv[]) {
    /*
    QApplication app(argc, argv);
    ScreenManager screenManager;
    screenManager.show();
    return app.exec();
     */

    SpriteFileManager manager;
    manager.createMapFromTextureFile();
}
