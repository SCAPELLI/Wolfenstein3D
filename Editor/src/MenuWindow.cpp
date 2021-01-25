#include <NewMapWindow.h>
#include "MenuWindow.h"
#include "ui_MenuWindow.h"

#define NEW_MAP_SCREEN 1

MenuWindow::MenuWindow(QWidget *parent, ScreenManager *screenManager)
    : QMainWindow(parent), ui(new Ui::MenuWindow) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;
    connectEvents();
}

MenuWindow::~MenuWindow() {
    delete this->ui;
}

void MenuWindow::connectEvents() {
    QPushButton* button = findChild<QPushButton*>("createMapButton");
    QObject::connect(button, &QPushButton::clicked, this, &MenuWindow::openCreateMapWindow);
}

void MenuWindow::openCreateMapWindow() {
    this->screenManager->changeScreen(NEW_MAP_SCREEN);
}
