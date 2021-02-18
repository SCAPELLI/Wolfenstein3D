#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <iostream>
#include <QtGui/QPainter>
#include "InfoScreen.h"
#include "ui_InfoScreen.h"
#include "../../common/Style.h"

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
    style.setButtonStyle(this->ui->acceptButton, 20, 50, 150);
    style.setButtonStyle(this->ui->cancelButton, 20, 50, 150);
    style.setRetroFont(this->ui->portLabel, 30);
    style.setRetroFont(this->ui->portLineEdit, 20);
    style.setRetroFont(this->ui->serverLabel, 30);
    style.setRetroFont(this->ui->serverLineEdit, 20);
}