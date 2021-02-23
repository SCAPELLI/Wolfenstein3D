/********************************************************************************
** Form generated from reading UI file 'NewMapDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMAPDIALOG_H
#define UI_NEWMAPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_NewMapDialog
{
public:
    QGridLayout *gridLayout;
    QLineEdit *lengthText;
    QLabel *label;
    QLineEdit *widthText;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *NewMapDialog)
    {
        if (NewMapDialog->objectName().isEmpty())
            NewMapDialog->setObjectName(QString::fromUtf8("NewMapDialog"));
        NewMapDialog->resize(366, 153);
        gridLayout = new QGridLayout(NewMapDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lengthText = new QLineEdit(NewMapDialog);
        lengthText->setObjectName(QString::fromUtf8("lengthText"));

        gridLayout->addWidget(lengthText, 0, 1, 1, 1);

        label = new QLabel(NewMapDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        widthText = new QLineEdit(NewMapDialog);
        widthText->setObjectName(QString::fromUtf8("widthText"));

        gridLayout->addWidget(widthText, 1, 1, 1, 1);

        label_2 = new QLabel(NewMapDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        okButton = new QPushButton(NewMapDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(NewMapDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);


        retranslateUi(NewMapDialog);

        QMetaObject::connectSlotsByName(NewMapDialog);
    } // setupUi

    void retranslateUi(QDialog *NewMapDialog)
    {
        NewMapDialog->setWindowTitle(QApplication::translate("NewMapDialog", "New Map", nullptr));
        label->setText(QApplication::translate("NewMapDialog", "Length", nullptr));
        label_2->setText(QApplication::translate("NewMapDialog", "Width", nullptr));
        okButton->setText(QApplication::translate("NewMapDialog", "Ok", nullptr));
        cancelButton->setText(QApplication::translate("NewMapDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewMapDialog: public Ui_NewMapDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMAPDIALOG_H
