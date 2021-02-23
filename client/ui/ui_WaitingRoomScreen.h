/********************************************************************************
** Form generated from reading UI file 'WaitingRoomScreen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAITINGROOMSCREEN_H
#define UI_WAITINGROOMSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WaitingRoomScreen
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *actualLabel;
    QLabel *slashLabel;
    QLabel *maxLabel;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_9;
    QLabel *levelLabel;
    QLabel *levelInputLabel;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QPushButton *refreshButton;
    QPushButton *startButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QWidget *WaitingRoomScreen)
    {
        if (WaitingRoomScreen->objectName().isEmpty())
            WaitingRoomScreen->setObjectName(QString::fromUtf8("WaitingRoomScreen"));
        WaitingRoomScreen->resize(670, 516);
        gridLayout_2 = new QGridLayout(WaitingRoomScreen);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 4, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_3, 0, 1, 1, 1);

        frame = new QFrame(WaitingRoomScreen);
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
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        actualLabel = new QLabel(frame);
        actualLabel->setObjectName(QString::fromUtf8("actualLabel"));
        actualLabel->setStyleSheet(QString::fromUtf8("color: red"));
        actualLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(actualLabel);

        slashLabel = new QLabel(frame);
        slashLabel->setObjectName(QString::fromUtf8("slashLabel"));
        slashLabel->setStyleSheet(QString::fromUtf8("color: red"));
        slashLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(slashLabel);

        maxLabel = new QLabel(frame);
        maxLabel->setObjectName(QString::fromUtf8("maxLabel"));
        maxLabel->setStyleSheet(QString::fromUtf8("color: red"));
        maxLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(maxLabel);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);


        gridLayout_3->addLayout(horizontalLayout_2, 3, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 4, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 3, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_9);

        levelLabel = new QLabel(frame);
        levelLabel->setObjectName(QString::fromUtf8("levelLabel"));
        levelLabel->setStyleSheet(QString::fromUtf8("color: red"));
        levelLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(levelLabel);

        levelInputLabel = new QLabel(frame);
        levelInputLabel->setObjectName(QString::fromUtf8("levelInputLabel"));
        levelInputLabel->setStyleSheet(QString::fromUtf8("color: red"));
        levelInputLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(levelInputLabel);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);


        gridLayout_3->addLayout(horizontalLayout_5, 1, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_7, 3, 2, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_5, 0, 1, 1, 1);


        gridLayout_2->addWidget(frame, 1, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelButton = new QPushButton(WaitingRoomScreen);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        refreshButton = new QPushButton(WaitingRoomScreen);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));

        horizontalLayout->addWidget(refreshButton);

        startButton = new QPushButton(WaitingRoomScreen);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        horizontalLayout->addWidget(startButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 1, 2, 1, 1);


        retranslateUi(WaitingRoomScreen);

        QMetaObject::connectSlotsByName(WaitingRoomScreen);
    } // setupUi

    void retranslateUi(QWidget *WaitingRoomScreen)
    {
        WaitingRoomScreen->setWindowTitle(QApplication::translate("WaitingRoomScreen", "Form", nullptr));
        actualLabel->setText(QApplication::translate("WaitingRoomScreen", "actual", nullptr));
        slashLabel->setText(QApplication::translate("WaitingRoomScreen", "/", nullptr));
        maxLabel->setText(QApplication::translate("WaitingRoomScreen", "max", nullptr));
        levelLabel->setText(QApplication::translate("WaitingRoomScreen", "Lvl:", nullptr));
        levelInputLabel->setText(QApplication::translate("WaitingRoomScreen", "level", nullptr));
        cancelButton->setText(QApplication::translate("WaitingRoomScreen", "Cancel", nullptr));
        refreshButton->setText(QApplication::translate("WaitingRoomScreen", "Refresh", nullptr));
        startButton->setText(QApplication::translate("WaitingRoomScreen", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WaitingRoomScreen: public Ui_WaitingRoomScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAITINGROOMSCREEN_H
