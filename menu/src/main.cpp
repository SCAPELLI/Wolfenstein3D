#include <iostream>
#include <QtWidgets/QApplication>
#include <MenuScreen.h>
#include <ScreenManager.h>
#include <StartScreen.h>

int initQt(int argc, char *argv[], Client *client) {
    QApplication app(argc, argv);
    ScreenManager screenManager(0, client);
    screenManager.show();
    int qtExitCode = app.exec();
    return 0;
}

int main(int argc, char *argv[]) {

    /**
    QApplication app(argc, argv);
     **/
    /**
    MenuScreen menuScreen;
    menuScreen.show();
     **/
/**
     ScreenManager screenManager;
     screenManager.show();

    return app.exec()''
**/

/////////////////
    Client client;
    initQt(argc, argv, &client);

    return 0;
}
