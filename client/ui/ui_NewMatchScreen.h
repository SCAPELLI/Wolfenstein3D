/********************************************************************************
** Form generated from reading UI file 'NewMatchScreen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMATCHSCREEN_H
#define UI_NEWMATCHSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewMatchScreen
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *acceptButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_5;
    QComboBox *maxPlayersBox;
    QLabel *maxPlayersLabel;
    QLabel *mapLabel;
    QComboBox *levelBox;

    void setupUi(QWidget *NewMatchScreen)
    {
        if (NewMatchScreen->objectName().isEmpty())
            NewMatchScreen->setObjectName(QString::fromUtf8("NewMatchScreen"));
        NewMatchScreen->resize(670, 516);
        gridLayout_2 = new QGridLayout(NewMatchScreen);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_3, 0, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 4, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        acceptButton = new QPushButton(NewMatchScreen);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));

        horizontalLayout->addWidget(acceptButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        cancelButton = new QPushButton(NewMatchScreen);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 3, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 1, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 1, 1, 1);

        frame = new QFrame(NewMatchScreen);
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
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_7, 3, 2, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 6, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 3, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_5, 0, 1, 1, 1);

        maxPlayersBox = new QComboBox(frame);
        maxPlayersBox->setObjectName(QString::fromUtf8("maxPlayersBox"));
        maxPlayersBox->setStyleSheet(QString::fromUtf8("background: red"));

        gridLayout_3->addWidget(maxPlayersBox, 5, 1, 1, 1);

        maxPlayersLabel = new QLabel(frame);
        maxPlayersLabel->setObjectName(QString::fromUtf8("maxPlayersLabel"));
        maxPlayersLabel->setStyleSheet(QString::fromUtf8("color: red"));
        maxPlayersLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(maxPlayersLabel, 4, 1, 1, 1);

        mapLabel = new QLabel(frame);
        mapLabel->setObjectName(QString::fromUtf8("mapLabel"));
        mapLabel->setStyleSheet(QString::fromUtf8("color: red"));
        mapLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(mapLabel, 1, 1, 1, 1);

        levelBox = new QComboBox(frame);
        levelBox->setObjectName(QString::fromUtf8("levelBox"));
        levelBox->setStyleSheet(QString::fromUtf8("background: red"));
        levelBox->setEditable(false);

        gridLayout_3->addWidget(levelBox, 3, 1, 1, 1);


        gridLayout_2->addWidget(frame, 1, 1, 1, 1);


        retranslateUi(NewMatchScreen);

        QMetaObject::connectSlotsByName(NewMatchScreen);
    } // setupUi

    void retranslateUi(QWidget *NewMatchScreen)
    {
        NewMatchScreen->setWindowTitle(QApplication::translate("NewMatchScreen", "Form", nullptr));
        acceptButton->setText(QApplication::translate("NewMatchScreen", "Accept", nullptr));
        cancelButton->setText(QApplication::translate("NewMatchScreen", "Cancel", nullptr));
        maxPlayersLabel->setText(QApplication::translate("NewMatchScreen", "Maximum number of players", nullptr));
        mapLabel->setText(QApplication::translate("NewMatchScreen", "Level", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewMatchScreen: public Ui_NewMatchScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMATCHSCREEN_H
