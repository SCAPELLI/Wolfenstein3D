#include <iostream>
#include <QtWidgets/QApplication>
#include <MenuScreen.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MenuScreen menuScreen;
    menuScreen.show();
    return app.exec();
}
