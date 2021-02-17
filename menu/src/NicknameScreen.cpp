#include "NicknameScreen.h"

#include "ui_NicknameScreen.h"
#include "../../common/Style.h"
#include "qpainter.h"
#include <QPaintEvent>


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
    this->screenManager->goNext();
}

void NicknameScreen::onCancelButtonClick() {
    this->screenManager->goBack();
}

void NicknameScreen::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap("../../resources/redBackground.png").scaled(size()));
    QWidget::paintEvent(event);

    /**
     * Asi lo repite:
    QPainter painter(this);
    QPixmap pixmap("../../resources/redBackground.png");
    painter.fillRect(event->rect(), QBrush(pixmap));
     **/
}

void NicknameScreen::setStyle() {
    Style style;
    style.setButtonStyle(this->ui->acceptButton, 20, 50, 150);
    style.setButtonStyle(this->ui->cancelButton, 20, 50, 150);
    style.setRetroFont(this->ui->nicknameLabel, 30);
    style.setRetroFont(this->ui->nicknameLineEdit, 20);
}