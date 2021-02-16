#include "NicknameScreen.h"

#include "ui_NicknameScreen.h"
#include "../../common/Style.h"
#include "qpainter.h"
#include <QPaintEvent>


NicknameScreen::NicknameScreen(QWidget *parent, ScreenManager *screenManager)
        : QWidget(parent), ui(new Ui::NicknameScreen) {
    this->ui->setupUi(this);
    this->setStyle();
}

NicknameScreen::~NicknameScreen() {
    delete this->ui;
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