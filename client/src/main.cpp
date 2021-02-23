#include <iostream>
#include <QtWidgets/QApplication>
#include <client/include/MenuScreen.h>
#include <client/include/ScreenManager.h>
#include <client/include/StartScreen.h>

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
    try {
        Client client;
        initQt(argc, argv, &client);
    } catch (const std::exception& error) {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
