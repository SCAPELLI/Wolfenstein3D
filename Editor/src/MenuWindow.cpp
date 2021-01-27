#include <NewMapWindow.h>
#include "MenuWindow.h"
#include "ui_MenuWindow.h"

#define EDITOR_SCREEN 1

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
    QObject::connect(button, &QPushButton::clicked, this, &MenuWindow::nextScreen);
}

void MenuWindow::nextScreen() {
    this->screenManager->changeScreen(EDITOR_SCREEN);
}
