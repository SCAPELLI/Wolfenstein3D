#include <MenuWindow.h>
#include <iostream>
#include <EditorScene.h>
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

    this->editorScene = new EditorScene(0, this);
    this->stack->addWidget(this->editorScene);

    this->stack->setCurrentIndex(0);
}

ScreenManager::~ScreenManager() {
    // Elimino los widgets almacenados en el stack
    int i;
    for (int i = this->stack->count() - 1; i >= 0; i--) {
       QWidget *widget = stack->widget(i);
       stack->removeWidget(widget);
    }
    delete this->ui;
    delete this->menuWindow;
    delete this->newMapWindow;
    delete this->editorScene;
}

void ScreenManager::changeScreen(int scene) {
    this->stack->setCurrentIndex(scene);
}

void ScreenManager::setMapFilePath() {
    EditorScene editorScene;
}