#include <MenuWindow.h>
#include <iostream>
#include <EditorScreen.h>
#include "../include/ScreenManager.h"
#include "ui_ScreenManager.h"

ScreenManager::ScreenManager(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ScreenManager) {
    this->ui->setupUi(this);

    this->stack = findChild<QStackedWidget*>("stack");

    this->menuWindow = new MenuWindow(0, this);
    this->stack->addWidget(this->menuWindow);

    this->editorScene = new EditorScreen(0, this);
    this->stack->addWidget(this->editorScene);

    this->stack->setCurrentIndex(0);
}

ScreenManager::~ScreenManager() {
    /**
     * Segun la documentacion, QStackedWidget tiene el ownership
     * de los objetos que se le agregan y realiza free en toda la
     * memoria pedida.
     **/
    delete this->ui;
}

void ScreenManager::changeScreen(int scene) {
    this->stack->setCurrentIndex(scene);
}