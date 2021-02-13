#include <iostream>
#include <QtWidgets/QApplication>
#include <MenuScreen.h>
#include <ScreenManager.h>
#include <StartScreen.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    /**
    MenuScreen menuScreen;
    menuScreen.show();
     **/

     ScreenManager screenManager;
     screenManager.show();

    return app.exec();
}
