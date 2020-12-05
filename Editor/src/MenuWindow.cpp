#include <iostream>
#include <NewMapWindow.h>
#include "../include/MenuWindow.h"
#include "ui_MenuWindow.h"

#define NEW_MAP 1

MenuWindow::MenuWindow(QWidget *parent, SceneManager *sceneManager)
    : QMainWindow(parent), ui(new Ui::MenuWindow) {
    this->ui->setupUi(this);
    this->sceneManager = sceneManager;
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
    this->sceneManager->changeScene(NEW_MAP);
}