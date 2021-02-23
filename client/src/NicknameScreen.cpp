#include "client/include/NicknameScreen.h"

#include "client/ui/ui_NicknameScreen.h"
#include "../../common/Style.h"
#include "qpainter.h"
#include <QPaintEvent>
#include <QtWidgets/QMessageBox>

#define BUTTON_FONT 20
#define BUTTON_HEIGHT 50
#define BUTTON_WIDTH 150
#define FIELD_FONT 20
#define LABEL_FONT 30

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
    style.setButtonStyle(this->ui->acceptButton, BUTTON_FONT,
                         BUTTON_HEIGHT, BUTTON_WIDTH);
    style.setButtonStyle(this->ui->cancelButton, BUTTON_FONT,
                         BUTTON_HEIGHT, BUTTON_WIDTH);
    style.setRetroFont(this->ui->nicknameLabel, LABEL_FONT);
    style.setRetroFont(this->ui->nicknameLineEdit, FIELD_FONT);
}