#include "NewMatchScreen.h"
#include "ui_NewMatchScreen.h"
#include "../../common/Style.h"

NewMatchScreen::NewMatchScreen(QWidget *parent, ScreenManager *screenManager)
    : QWidget(parent), ui(new Ui::NewMatchScreen) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;

    this->setStyle();
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

void NewMatchScreen::setStyle() {
    Style style;
    style.setButtonStyle(this->ui->acceptButton, 20, 50, 150);
    style.setButtonStyle(this->ui->cancelButton, 20, 50, 150);

    style.setRetroFont(this->ui->mapLabel, 30);
    style.setRetroFont(this->ui->maxPlayersLabel, 30);
    style.setRetroFont(this->ui->levelLineEdit, 20);
    style.setRetroFont(this->ui->maxPlayersLineEdit, 20);

}