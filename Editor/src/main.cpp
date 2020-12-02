#include <iostream>
#include <QtWidgets/QApplication>
#include <MenuWindow.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MenuWindow menu;
    menu.show();
    return app.exec();

    return 0;
}
