/********************************************************************************
** Form generated from reading UI file 'ScreenManager.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENMANAGER_H
#define UI_SCREENMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScreenManager
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *screens;

    void setupUi(QMainWindow *ScreenManager)
    {
        if (ScreenManager->objectName().isEmpty())
            ScreenManager->setObjectName(QString::fromUtf8("ScreenManager"));
        ScreenManager->resize(800, 600);
        ScreenManager->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(ScreenManager);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        screens = new QStackedWidget(centralwidget);
        screens->setObjectName(QString::fromUtf8("screens"));

        gridLayout->addWidget(screens, 0, 0, 1, 1);

        ScreenManager->setCentralWidget(centralwidget);

        retranslateUi(ScreenManager);

        QMetaObject::connectSlotsByName(ScreenManager);
    } // setupUi

    void retranslateUi(QMainWindow *ScreenManager)
    {
        ScreenManager->setWindowTitle(QApplication::translate("ScreenManager", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScreenManager: public Ui_ScreenManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENMANAGER_H
