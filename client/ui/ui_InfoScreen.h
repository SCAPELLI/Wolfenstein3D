/********************************************************************************
** Form generated from reading UI file 'InfoScreen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFOSCREEN_H
#define UI_INFOSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InfoScreen
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *acceptButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer_4;
    QLineEdit *portLineEdit;
    QSpacerItem *verticalSpacer_5;
    QLabel *serverLabel;
    QLabel *portLabel;
    QLineEdit *serverLineEdit;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *InfoScreen)
    {
        if (InfoScreen->objectName().isEmpty())
            InfoScreen->setObjectName(QString::fromUtf8("InfoScreen"));
        InfoScreen->resize(670, 516);
        gridLayout_2 = new QGridLayout(InfoScreen);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_3, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 4, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        acceptButton = new QPushButton(InfoScreen);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));

        horizontalLayout->addWidget(acceptButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        cancelButton = new QPushButton(InfoScreen);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 3, 1, 1, 1);

        frame = new QFrame(InfoScreen);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(100);
        sizePolicy.setVerticalStretch(50);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setStyleSheet(QString::fromUtf8("background: rgb(80, 0, 0);\n"
"border:  0"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 6, 1, 1, 1);

        portLineEdit = new QLineEdit(frame);
        portLineEdit->setObjectName(QString::fromUtf8("portLineEdit"));
        portLineEdit->setStyleSheet(QString::fromUtf8("background: red"));

        gridLayout_3->addWidget(portLineEdit, 3, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_5, 0, 1, 1, 1);

        serverLabel = new QLabel(frame);
        serverLabel->setObjectName(QString::fromUtf8("serverLabel"));
        serverLabel->setStyleSheet(QString::fromUtf8("color: red"));
        serverLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(serverLabel, 4, 1, 1, 1);

        portLabel = new QLabel(frame);
        portLabel->setObjectName(QString::fromUtf8("portLabel"));
        portLabel->setStyleSheet(QString::fromUtf8("color: red"));
        portLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(portLabel, 2, 1, 1, 1);

        serverLineEdit = new QLineEdit(frame);
        serverLineEdit->setObjectName(QString::fromUtf8("serverLineEdit"));
        serverLineEdit->setStyleSheet(QString::fromUtf8("background: red"));

        gridLayout_3->addWidget(serverLineEdit, 5, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_7, 4, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 4, 0, 1, 1);


        gridLayout_2->addWidget(frame, 1, 1, 1, 1);


        retranslateUi(InfoScreen);

        QMetaObject::connectSlotsByName(InfoScreen);
    } // setupUi

    void retranslateUi(QWidget *InfoScreen)
    {
        InfoScreen->setWindowTitle(QApplication::translate("InfoScreen", "Form", nullptr));
        acceptButton->setText(QApplication::translate("InfoScreen", "Accept", nullptr));
        cancelButton->setText(QApplication::translate("InfoScreen", "Cancel", nullptr));
        serverLabel->setText(QApplication::translate("InfoScreen", "Server:", nullptr));
        portLabel->setText(QApplication::translate("InfoScreen", "Port:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InfoScreen: public Ui_InfoScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOSCREEN_H
