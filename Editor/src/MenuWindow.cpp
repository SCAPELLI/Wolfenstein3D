#include <iostream>
#include <NewMapWindow.h>
#include "../include/MenuWindow.h"
#include "ui_MenuWindow.h"

MenuWindow::MenuWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MenuWindow) {
    this->ui->setupUi(this);
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
    this->newMapWindow = new NewMapWindow(this);
    this->newMapWindow->show();
}