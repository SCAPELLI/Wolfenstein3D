#include <QtWidgets/QPushButton>
#include "InfoScreen.h"
#include "ui_InfoScreen.h"

InfoScreen::InfoScreen(QWidget *parent, ScreenManager *screenManager)
    : QWidget(parent), ui(new Ui::InfoScreen) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;

    connectEvents();
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
    this->screenManager->goNext();
}

void InfoScreen::onCancelButtonClick() {
    this->screenManager->goBack();
}