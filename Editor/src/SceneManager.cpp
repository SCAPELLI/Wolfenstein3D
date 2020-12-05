#include <MenuWindow.h>
#include <iostream>
#include "../include/SceneManager.h"
#include "ui_SceneManager.h"

SceneManager::SceneManager(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SceneManager) {
    this->ui->setupUi(this);
    this->stack =findChild<QStackedWidget*>("stack");
    this->stack->addWidget(new MenuWindow(0, this));
    this->stack->addWidget(new NewMapWindow(0, this));
    this->stack->setCurrentIndex(0);
}

SceneManager::~SceneManager() {
    // Elimino los widgets almacenados en el stack
    int i;
    for (int i = this->stack->count(); i >= 0; i--) {
       QWidget *widget = stack->widget(i);
       stack->removeWidget(widget);
       delete widget;
    }
    delete this->ui;
}

void SceneManager::changeScene(int scene) {
    this->stack->setCurrentIndex(scene);
}
