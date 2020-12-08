#include <iostream>
#include <QtWidgets/QApplication>
#include <MenuWindow.h>
#include <NewMapWindow.h>
#include <Editor.h>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <ScreenManager.h>
#include <EditorScene.h>

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



}
