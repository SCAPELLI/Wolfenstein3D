#include <QtGui/QFontDatabase>
#include <iostream>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include "MenuWindow.h"
#include "ui_MenuWindow.h"
#include "../../common/Style.h"

#define EDITOR_SCREEN 1

#define TITLE_WIDTH 516
#define TITLE_HEIGHT 120
#define TITLE_FONT_SIZE 25
#define BUTTON_FONT_SIZE 15

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
    this->ui->titleLabel->setPixmap(title.scaled(TITLE_WIDTH, TITLE_HEIGHT, Qt::KeepAspectRatio));

    Style style;
    style.setRetroFont(static_cast<QWidget*>(this->ui->subtitleLabel), TITLE_FONT_SIZE);
    style.setButtonStyle(this->ui->createMapButton, BUTTON_FONT_SIZE);
    style.setBrickBackgroundToScreen(this);
}