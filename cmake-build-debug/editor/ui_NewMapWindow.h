/********************************************************************************
** Form generated from reading UI file 'NewMapWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMAPWINDOW_H
#define UI_NEWMAPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewMapWindow
{
public:
    QWidget *centralwidget;
    QWidget *formLayoutWidget;
    QFormLayout *infoMapLayout;
    QLabel *label;
    QLineEdit *nameMap;
    QLabel *label_2;
    QLineEdit *lengthMap;
    QLabel *label_3;
    QLineEdit *widthMap;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *acceptButton;
    QPushButton *cancelButton;

    void setupUi(QMainWindow *NewMapWindow)
    {
        if (NewMapWindow->objectName().isEmpty())
            NewMapWindow->setObjectName(QString::fromUtf8("NewMapWindow"));
        NewMapWindow->resize(502, 239);
        centralwidget = new QWidget(NewMapWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(79, 30, 351, 98));
        infoMapLayout = new QFormLayout(formLayoutWidget);
        infoMapLayout->setObjectName(QString::fromUtf8("infoMapLayout"));
        infoMapLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        infoMapLayout->setWidget(0, QFormLayout::LabelRole, label);

        nameMap = new QLineEdit(formLayoutWidget);
        nameMap->setObjectName(QString::fromUtf8("nameMap"));

        infoMapLayout->setWidget(0, QFormLayout::FieldRole, nameMap);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        infoMapLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lengthMap = new QLineEdit(formLayoutWidget);
        lengthMap->setObjectName(QString::fromUtf8("lengthMap"));

        infoMapLayout->setWidget(1, QFormLayout::FieldRole, lengthMap);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        infoMapLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        widthMap = new QLineEdit(formLayoutWidget);
        widthMap->setObjectName(QString::fromUtf8("widthMap"));

        infoMapLayout->setWidget(2, QFormLayout::FieldRole, widthMap);

        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(160, 120, 188, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        acceptButton = new QPushButton(horizontalLayoutWidget);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));

        horizontalLayout->addWidget(acceptButton);

        cancelButton = new QPushButton(horizontalLayoutWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        NewMapWindow->setCentralWidget(centralwidget);

        retranslateUi(NewMapWindow);

        QMetaObject::connectSlotsByName(NewMapWindow);
    } // setupUi

    void retranslateUi(QMainWindow *NewMapWindow)
    {
        NewMapWindow->setWindowTitle(QApplication::translate("NewMapWindow", "New map info", nullptr));
        label->setText(QApplication::translate("NewMapWindow", "Name", nullptr));
        nameMap->setText(QString());
        label_2->setText(QApplication::translate("NewMapWindow", "Length", nullptr));
        label_3->setText(QApplication::translate("NewMapWindow", "Width", nullptr));
        acceptButton->setText(QApplication::translate("NewMapWindow", "Accept", nullptr));
        cancelButton->setText(QApplication::translate("NewMapWindow", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewMapWindow: public Ui_NewMapWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMAPWINDOW_H
