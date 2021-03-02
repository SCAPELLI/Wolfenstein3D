#include <QtWidgets/QMessageBox>
#include <QtWidgets/QComboBox>
#include "client/include/NewMatchScreen.h"
#include "client/ui/ui_NewMatchScreen.h"
#include "common/include/Style.h"

#define BUTTON_FONT 20
#define BUTTON_HEIGHT 50
#define BUTTON_WIDTH 150
#define FIELD_FONT 20
#define LABEL_FONT 30

#define LEVELS_MAX_LEVEL 8
#define PLAYERS_MIN_ALLOWED 2
#define PLAYERS_MAX_ALLOWED 6

const QStringList createQStringListOfNumbers(int min, int max);

NewMatchScreen::NewMatchScreen(QWidget *parent, ScreenManager *screenManager)
    : QWidget(parent), ui(new Ui::NewMatchScreen) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;

    this->setOptions();
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
    QComboBox *levelBox = findChild<QComboBox*>("levelBox");
    QComboBox *maxPlayersBox = findChild<QComboBox*>("maxPlayersBox");

    if (this->screenManager->tryToCreateAMatch(levelBox->currentText().toInt(),
                                               maxPlayersBox->currentText().toInt())) {
        this->screenManager->refreshWaitingRoom();
        this->screenManager->goNext();
    } else {
        QMessageBox badInputMessage;
        badInputMessage.setText("An error has occurred");
        badInputMessage.exec();
    }

}

void NewMatchScreen::onCancelButtonClick() {
    this->screenManager->goBack();
}

void NewMatchScreen::setOptions() {
    QComboBox *levelBox = findChild<QComboBox*>("levelBox");
    QStringList levelList = createQStringListOfNumbers(1, LEVELS_MAX_LEVEL);
    levelBox->addItems(levelList);

    QComboBox *maxPlayersBox = findChild<QComboBox*>("maxPlayersBox");
    QStringList maxPlayerList = createQStringListOfNumbers(PLAYERS_MIN_ALLOWED, PLAYERS_MAX_ALLOWED);
    maxPlayersBox->addItems(maxPlayerList);
}

void NewMatchScreen::setStyle() {
    Style style;
    style.setButtonStyle(this->ui->acceptButton, BUTTON_FONT,
                         BUTTON_HEIGHT, BUTTON_WIDTH);
    style.setButtonStyle(this->ui->cancelButton, BUTTON_FONT,
                         BUTTON_HEIGHT, BUTTON_WIDTH);

    style.setRetroFont(this->ui->mapLabel, LABEL_FONT);
    style.setRetroFont(this->ui->maxPlayersLabel, LABEL_FONT);

    style.setRetroFont(this->ui->levelBox, FIELD_FONT);
    style.setRetroFont(this->ui->maxPlayersBox, FIELD_FONT);
}

const QStringList createQStringListOfNumbers(int min, int max) {
    QStringList list = {};
    for (int i = min; i != max + 1; i++) {
        list.append(QString::number(i));
    }
    return list;
}