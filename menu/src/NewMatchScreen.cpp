#include <QtWidgets/QMessageBox>
#include <QtWidgets/QComboBox>
#include "NewMatchScreen.h"
#include "ui_NewMatchScreen.h"
#include "../../common/Style.h"

#define BUTTON_FONT 20
#define BUTTON_HEIGHT 50
#define BUTTON_WIDTH 150
#define FIELD_FONT 20
#define LABEL_FONT 30

NewMatchScreen::NewMatchScreen(QWidget *parent, ScreenManager *screenManager)
    : QWidget(parent), ui(new Ui::NewMatchScreen) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;

    this->setLevels();

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
    QLineEdit *maxPlayersLineEdit = findChild<QLineEdit*>("maxPlayersLineEdit");

    if (this->screenManager->tryToCreateAMatch(levelBox->currentText().toInt(),
                                               maxPlayersLineEdit->text().toInt())) {
        this->screenManager->refreshWaitingRoom();
        this->screenManager->goNext();
    } else {
        QMessageBox badInputMessage;
        badInputMessage.setText("Invalid fields");
        badInputMessage.exec();
        maxPlayersLineEdit->clear();
    }

}

void NewMatchScreen::onCancelButtonClick() {
    this->screenManager->goBack();
}

void NewMatchScreen::setLevels() {
    QComboBox *levelBox = findChild<QComboBox*>("levelBox");
    QStringList levelList = {"1"};
    levelBox->addItems(levelList);
}

void NewMatchScreen::setStyle() {
    Style style;
    style.setButtonStyle(this->ui->acceptButton, BUTTON_FONT, BUTTON_HEIGHT, BUTTON_WIDTH);
    style.setButtonStyle(this->ui->cancelButton, BUTTON_FONT, BUTTON_HEIGHT, BUTTON_WIDTH);

    style.setRetroFont(this->ui->mapLabel, LABEL_FONT);
    style.setRetroFont(this->ui->maxPlayersLabel, LABEL_FONT);
    style.setRetroFont(this->ui->maxPlayersLineEdit, FIELD_FONT);

    style.setRetroFont(this->ui->levelBox, FIELD_FONT);

}