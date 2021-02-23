#include <iostream>
#include <QtWidgets/QApplication>
#include <MenuScreen.h>
#include <ScreenManager.h>
#include <StartScreen.h>
#include <ScoreWindow.h>

int initQt(int argc, char *argv[], Client *client) {
    QApplication app(argc, argv);
    ScreenManager screenManager(0, client);
    screenManager.show();
    int qtExitCode = app.exec();
    return 0;
}

int main(int argc, char *argv[]) {
    /**
    try {
        Client client;
        initQt(argc, argv, &client);
    } catch (const std::exception& error) {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
    **/

    std::map<std::string, std::vector<int>> names;
    names["juan"] = {150, 10, 50};
    names["lu"] = {120, 9, 45};
    names["nick"] = {35, 5, 25};
    names["sebas"] = {130, 7, 35};

    QApplication app(argc, argv);
    ScoreWindow screenManager(0, names);
    screenManager.show();
    return app.exec();

}
