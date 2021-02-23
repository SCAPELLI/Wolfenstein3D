/********************************************************************************
** Form generated from reading UI file 'MenuScreen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUSCREEN_H
#define UI_MENUSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuScreen
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QPushButton *startButton;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_2;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *acceptButton;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QLineEdit *nicknameLine;
    QLabel *nicknameLabel;
    QSpacerItem *verticalSpacer_6;
    QWidget *page_3;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_9;
    QLabel *label;
    QSpacerItem *verticalSpacer_7;
    QListWidget *listWidget;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_7;

    void setupUi(QMainWindow *MenuScreen)
    {
        if (MenuScreen->objectName().isEmpty())
            MenuScreen->setObjectName(QString::fromUtf8("MenuScreen"));
        MenuScreen->resize(800, 600);
        centralwidget = new QWidget(MenuScreen);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout_2 = new QGridLayout(page);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 1, 1);

        startButton = new QPushButton(page);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        startButton->setFont(font);
        startButton->setStyleSheet(QString::fromUtf8("background: none;\n"
"border: none;\n"
"margin: 0;\n"
"padding: 0;\n"
"color: rgb(170, 0, 0);\n"
"font-weight: bold;\n"
"outline: none;"));

        gridLayout_2->addWidget(startButton, 2, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 3, 1, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayout_3 = new QGridLayout(page_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_5, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        acceptButton = new QPushButton(page_2);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));
        acceptButton->setStyleSheet(QString::fromUtf8("background: rgb(85, 0, 0);\n"
"border: rgb(85, 0, 0);\n"
"color: rgb(162, 162, 162);\n"
"font-weight: bold;\n"
"outline: none;\n"
""));

        horizontalLayout->addWidget(acceptButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        cancelButton = new QPushButton(page_2);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setStyleSheet(QString::fromUtf8("background: rgb(85, 0, 0);\n"
"border: rgb(85, 0, 0);\n"
"color: rgb(162, 162, 162);\n"
"font-weight: bold;\n"
"outline: none;\n"
""));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout_3->addLayout(horizontalLayout, 4, 0, 1, 2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 3, 0, 1, 1);

        nicknameLine = new QLineEdit(page_2);
        nicknameLine->setObjectName(QString::fromUtf8("nicknameLine"));
        nicknameLine->setStyleSheet(QString::fromUtf8("background: rgb(85, 0, 0);\n"
"border: rgb(85, 0, 0);\n"
"color: rgb(162, 162, 162);\n"
"font-weight: bold;\n"
"outline: none;\n"
""));

        gridLayout_3->addWidget(nicknameLine, 2, 0, 1, 2);

        nicknameLabel = new QLabel(page_2);
        nicknameLabel->setObjectName(QString::fromUtf8("nicknameLabel"));
        nicknameLabel->setLayoutDirection(Qt::LeftToRight);
        nicknameLabel->setStyleSheet(QString::fromUtf8("color: rgb(162, 162, 162);\n"
"font-weight: bold;\n"
""));
        nicknameLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_3->addWidget(nicknameLabel, 1, 0, 1, 2);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_6, 5, 0, 1, 1);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        verticalLayout = new QVBoxLayout(page_3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_9);

        label = new QLabel(page_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("color: rgb(162, 162, 162);\n"
"font-weight: bold;\n"
""));

        verticalLayout->addWidget(label);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_7);

        listWidget = new QListWidget(page_3);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_8);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        pushButton = new QPushButton(page_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8("background: rgb(85, 0, 0);\n"
"border: rgb(85, 0, 0);\n"
"color: rgb(162, 162, 162);\n"
"font-weight: bold;\n"
"outline: none;"));

        horizontalLayout_3->addWidget(pushButton);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_3);

        stackedWidget->addWidget(page_3);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        MenuScreen->setCentralWidget(centralwidget);

        retranslateUi(MenuScreen);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MenuScreen);
    } // setupUi

    void retranslateUi(QMainWindow *MenuScreen)
    {
        MenuScreen->setWindowTitle(QApplication::translate("MenuScreen", "MainWindow", nullptr));
        startButton->setText(QApplication::translate("MenuScreen", "START", nullptr));
        acceptButton->setText(QApplication::translate("MenuScreen", "ACCEPT", nullptr));
        cancelButton->setText(QApplication::translate("MenuScreen", "CANCEL", nullptr));
        nicknameLabel->setText(QApplication::translate("MenuScreen", "Nickname:", nullptr));
        label->setText(QApplication::translate("MenuScreen", "Servers:", nullptr));
        pushButton->setText(QApplication::translate("MenuScreen", "JOIN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuScreen: public Ui_MenuScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUSCREEN_H
