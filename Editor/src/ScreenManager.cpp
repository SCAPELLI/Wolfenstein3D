#include <MenuWindow.h>
#include <iostream>
#include <EditorScene.h>
#include "../include/ScreenManager.h"
#include "ui_ScreenManager.h"

ScreenManager::ScreenManager(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ScreenManager) {
    this->ui->setupUi(this);
    this->stack =findChild<QStackedWidget*>("stack");
    this->stack->addWidget(new MenuWindow(0, this));
    this->stack->addWidget(new NewMapWindow(0, this));
    this->stack->addWidget(new EditorScene(0, this));
    this->stack->setCurrentIndex(2);
}

ScreenManager::~ScreenManager() {
    // Elimino los widgets almacenados en el stack
    int i;
    for (int i = this->stack->count() - 1; i >= 0; i--) {
       QWidget *widget = stack->widget(i);
       stack->removeWidget(widget);
       delete widget;
    }
    delete this->ui;
}

void ScreenManager::changeScreen(int scene) {
    this->stack->setCurrentIndex(scene);
}

void ScreenManager::setMapFilePath() {
    EditorScene editorScene;
}