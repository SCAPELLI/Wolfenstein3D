#include <NewMapWindow.h>
#include <QtGui/QFontDatabase>
#include <iostream>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include "MenuWindow.h"
#include "ui_MenuWindow.h"
#include "../Style.h"

#define EDITOR_SCREEN 1

MenuWindow::MenuWindow(QWidget *parent, ScreenManager *screenManager)
    : QMainWindow(parent), ui(new Ui::MenuWindow) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;

    this->setStyle();

    this->connectEvents();
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

void MenuWindow::setStyle() {
    QPixmap title("../resources/title.png");
    this->ui->titleLabel->setPixmap(title.scaled(516, 120, Qt::KeepAspectRatio));

    Style style;
    style.setRetroFont(static_cast<QWidget*>(this->ui->subtitleLabel), 25);
    style.setButtonStyle(this->ui->createMapButton, 15);
    style.setBrickBackgroundToScreen(this);
}