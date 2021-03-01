#include <iostream>
#include <QtWidgets/QApplication>
#include <client/include/MenuScreen.h>
#include <client/include/ScreenManager.h>
#include <client/include/StartScreen.h>
#include <client/include/ScoreWindow.h>

int initQt(int argc, char *argv[], Client *client) {
    QApplication app(argc, argv);
    ScreenManager screenManager(0, client);
    client->setScreenManager(&screenManager);
    screenManager.show();
    int qtExitCode = app.exec();
    return 0;
}

int showHighscores(int argc, char *argv[], std::map<std::string, std::vector<int>> names) {
    QApplication app(argc, argv);
    ScoreWindow scoreWindow(0, names);
    scoreWindow.show();
    int qtExitCode = app.exec();
    return 0;
}

int main(int argc, char *argv[]) {
    try {
        Client client;
        initQt(argc, argv, &client);
        /**
         * showHighscores(int argc, char *argv[], std::map<std::string, std::vector<int>> names)
         * hay que ver como obtener el vector ese
         */
    } catch (const std::exception& error) {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
