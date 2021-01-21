#include <QtWidgets/QMessageBox>
#include <iostream>
#include "NewMapDialog.h"
#include "ui_NewMapDialog.h"

static bool validateInput(const QString &input, int *result);

NewMapDialog::NewMapDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::NewMapDialog){
    this->ui->setupUi(this);
    this->validState = false;
    connectEvents();
}

NewMapDialog::~NewMapDialog() {
    delete this->ui;
}

void NewMapDialog::connectEvents() {
    QPushButton* acceptButton = findChild<QPushButton*>("okButton");
    QObject::connect(acceptButton, &QPushButton::clicked, this, &NewMapDialog::accept);

    QPushButton* cancelButton = findChild<QPushButton*>("cancelButton");
    QObject::connect(cancelButton, &QPushButton::clicked, this, &NewMapDialog::close);
}

void NewMapDialog::accept() {
    QLineEdit* lenght = findChild<QLineEdit*>("lengthText");
    QLineEdit* width = findChild<QLineEdit*>("widthText");

    int lenghtNumber;
    int widthNumber;

    if (validateInput(lenght->text(), &lenghtNumber) && validateInput(width->text(), &widthNumber)) {
        this->validState = true;
        this->hide();
        return;
    }

    QMessageBox badInputMessage;
    badInputMessage.setText("Ha ingresado mal alguno de los campos");
    badInputMessage.exec();
}

void NewMapDialog::close() {
    this->hide();
}

bool NewMapDialog::giveLenghtWidthIfHasAValidState(int *lenght, int *width) {
    if (this->validState) {
        QLineEdit* lenghtText = findChild<QLineEdit*>("lengthText");
        QLineEdit* widthText = findChild<QLineEdit*>("widthText");
        *lenght = lenghtText->text().toInt();
        *width = widthText->text().toInt();
        return true;
    }
    *lenght = -1;
    *width = -1;
    return false;
}

static bool validateInput(const QString &input, int *result) {
    bool isInt;
    int number = input.toInt(&isInt);
    if (isInt) {
        if (number > 0) {
            *result = number;
            return true;
        }
    }
    *result = -1;
    return false;
}