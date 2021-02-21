#include "NicknameScreen.h"

#include "ui_NicknameScreen.h"
#include "../../common/Style.h"
#include "qpainter.h"
#include <QPaintEvent>
#include <QtWidgets/QMessageBox>


NicknameScreen::NicknameScreen(QWidget *parent, ScreenManager *screenManager)
        : QWidget(parent), ui(new Ui::NicknameScreen) {
    this->ui->setupUi(this);
    this->screenManager = screenManager;
    this->setStyle();

    connectEvents();
}

NicknameScreen::~NicknameScreen() {
    delete this->ui;
}

void NicknameScreen::connectEvents() {
    QPushButton *acceptButton = findChild<QPushButton*>("acceptButton");
    QObject::connect(acceptButton, &QPushButton::clicked, this, &NicknameScreen::onAcceptButtonClick);

    QPushButton *cancelButton = findChild<QPushButton*>("cancelButton");
    QObject::connect(cancelButton, &QPushButton::clicked, this, &NicknameScreen::onCancelButtonClick);
}

void NicknameScreen::onAcceptButtonClick() {
    QLineEdit *nicknameLine = findChild<QLineEdit*>("nicknameLineEdit");

    if (this->screenManager->tryToSubmitUsername(nicknameLine->text().toStdString())) {
        this->screenManager->goNext();
    } else {
        QMessageBox badInputMessage;
        badInputMessage.setText("Invalid username");
        badInputMessage.exec();
        nicknameLine->clear();
    }
}

void NicknameScreen::onCancelButtonClick() {
    this->screenManager->goBack();
}

void NicknameScreen::setStyle() {
    Style style;
    style.setButtonStyle(this->ui->acceptButton, 20, 50, 150);
    style.setButtonStyle(this->ui->cancelButton, 20, 50, 150);
    style.setRetroFont(this->ui->nicknameLabel, 30);
    style.setRetroFont(this->ui->nicknameLineEdit, 20);
}