#include <QtWidgets/QStyleOption>
#include "client/include/StartScreen.h"
#include "qpainter.h"
#include "client/ui/ui_StartScreen.h"
#include "common/Style.h"


StartScreen::StartScreen(QWidget *parent, ScreenManager *screenManager)
    : QWidget(parent), ui(new Ui::StartScreen) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;
    this->setStyle();
    connectEvents();
}

StartScreen::~StartScreen() {
    delete this->ui;
}

void StartScreen::connectEvents() {
    QPushButton *startButton = findChild<QPushButton*>("startButton");
    QObject::connect(startButton, &QPushButton::clicked, this, &StartScreen::clickJoinButton);
}

void StartScreen::clickJoinButton() {
    this->screenManager->goNext();
}

void StartScreen::setStyle() {
    QString sheetStyle =
            "QPushButton {"
                "background: none;"
                "border: none;"
                "margin: 0;"
                "padding: 0;"
                "color: rgb(170, 0, 0);"
                "font-weight: bold;"
                "outline: none"
            "}"
            "QPushButton:hover {"
            "color: rgb(220, 0, 0)"
            "}"
            "QPushButton:pressed {"
                "color: rgb(80, 0, 0)"
            "}";
    Style style;
    this->ui->startButton->setStyleSheet(sheetStyle);
    style.setRetroFont(this->ui->startButton, 25);
}