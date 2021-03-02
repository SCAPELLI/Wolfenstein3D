#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <iostream>
#include <QtGui/QPainter>
#include "InfoScreen.h"
#include "ui_InfoScreen.h"
#include "common/include/Style.h"

#define BUTTON_FONT 20
#define BUTTON_HEIGHT 50
#define BUTTON_WIDTH 150
#define FIELD_FONT 20
#define LABEL_FONT 30

InfoScreen::InfoScreen(QWidget *parent, ScreenManager *screenManager)
    : QWidget(parent), ui(new Ui::InfoScreen) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;

    this->setStyle();
    this->connectEvents();
}

InfoScreen::~InfoScreen() {
    delete this->ui;
}

void InfoScreen::connectEvents() {
    QPushButton *acceptButton = findChild<QPushButton*>("acceptButton");
    QObject::connect(acceptButton, &QPushButton::clicked, this, &InfoScreen::onAcceptButtonClick);

    QPushButton *cancelButton = findChild<QPushButton*>("cancelButton");
    QObject::connect(cancelButton, &QPushButton::clicked, this, &InfoScreen::onCancelButtonClick);
}

void InfoScreen::onAcceptButtonClick() {
    QLineEdit *portLine = findChild<QLineEdit*>("portLineEdit");
    QLineEdit *serverLine = findChild<QLineEdit*>("serverLineEdit");
    if (this->screenManager->tryToConnect(portLine->text().toStdString(), serverLine->text().toStdString())) {
        this->screenManager->goNext();
    } else {
        //sacar mensaje de error al conectarse, reintentar
        portLine->clear();
        serverLine->clear();
    }
}

void InfoScreen::onCancelButtonClick() {
    this->screenManager->goBack();
}

void InfoScreen::setStyle() {
    Style style;
    style.setButtonStyle(this->ui->acceptButton, BUTTON_FONT,
                         BUTTON_HEIGHT, BUTTON_WIDTH);
    style.setButtonStyle(this->ui->cancelButton, BUTTON_FONT,
                         BUTTON_HEIGHT, BUTTON_WIDTH);
    style.setRetroFont(this->ui->portLabel, LABEL_FONT);
    style.setRetroFont(this->ui->portLineEdit, FIELD_FONT);
    style.setRetroFont(this->ui->serverLabel, LABEL_FONT);
    style.setRetroFont(this->ui->serverLineEdit, FIELD_FONT);
}