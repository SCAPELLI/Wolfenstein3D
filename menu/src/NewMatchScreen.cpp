#include "NewMatchScreen.h"
#include "ui_NewMatchScreen.h"

NewMatchScreen::NewMatchScreen(QWidget *parent, ScreenManager *screenManager)
    : QWidget(parent), ui(new Ui::NewMatchScreen) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;

    this->connectEvents();
}

NewMatchScreen::~NewMatchScreen() {
    delete this->ui;
}

void NewMatchScreen::connectEvents() {
    QPushButton *acceptButton = findChild<QPushButton*>("acceptButton");
    QObject::connect(acceptButton, &QPushButton::clicked, this, &NewMatchScreen::onAcceptButtonClick);

    QPushButton *cancelButton = findChild<QPushButton*>("cancelButton");
    QObject::connect(cancelButton, &QPushButton::clicked, this, &NewMatchScreen::onCancelButtonClick);

}

void NewMatchScreen::onAcceptButtonClick() {
    QLineEdit *levelLineEdit = findChild<QLineEdit*>("levelLineEdit");
    QLineEdit *maxPlayersLineEdit = findChild<QLineEdit*>("maxPlayersLineEdit");

    if (this->screenManager->tryToCreateAMatch(levelLineEdit->text().toInt(),
                                               maxPlayersLineEdit->text().toInt())) {
        //this->screenManager->refreshWaitingRoom();
        this->screenManager->goNext();
    } else {
        //sacar mensaje de error
        levelLineEdit->clear();
        maxPlayersLineEdit->clear();
    }

}

void NewMatchScreen::onCancelButtonClick() {
    this->screenManager->goBack();
}