#include <MenuWindow.h>
#include <iostream>
#include <EditorScreen.h>
#include "../include/ScreenManager.h"
#include "ui_ScreenManager.h"

ScreenManager::ScreenManager(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ScreenManager) {
    this->ui->setupUi(this);
    this->stack =findChild<QStackedWidget*>("stack");

    this->menuWindow = new MenuWindow(0, this);
    this->stack->addWidget(this->menuWindow);

    this->newMapWindow = new NewMapWindow(0, this);
    this->stack->addWidget(this->newMapWindow);

    this->editorScene = new EditorScreen(0, this);
    this->stack->addWidget(this->editorScene);

    this->stack->setCurrentIndex(0);
}

ScreenManager::~ScreenManager() {
    int i;
    for (int i = this->stack->count() - 1; i >= 0; i--) {
       QWidget *widget = stack->widget(i);
       stack->removeWidget(widget);
    }
    delete this->menuWindow;
    delete this->newMapWindow;
    delete this->editorScene;
    delete this->ui;
}

void ScreenManager::changeScreen(int scene) {
    this->stack->setCurrentIndex(scene);
}

void ScreenManager::setMapSize(size_t rows, size_t columns) {
    this->editorScene->setMapSize(rows, columns);
}