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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScreenManager
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stack;

    void setupUi(QMainWindow *ScreenManager)
    {
        if (ScreenManager->objectName().isEmpty())
            ScreenManager->setObjectName(QString::fromUtf8("ScreenManager"));
        ScreenManager->resize(547, 414);
        centralwidget = new QWidget(ScreenManager);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        stack = new QStackedWidget(centralwidget);
        stack->setObjectName(QString::fromUtf8("stack"));

        horizontalLayout->addWidget(stack);

        ScreenManager->setCentralWidget(centralwidget);

        retranslateUi(ScreenManager);

        stack->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(ScreenManager);
    } // setupUi

    void retranslateUi(QMainWindow *ScreenManager)
    {
        ScreenManager->setWindowTitle(QApplication::translate("ScreenManager", "Wolfenstein 3D Map Editor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScreenManager: public Ui_ScreenManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENMANAGER_H
