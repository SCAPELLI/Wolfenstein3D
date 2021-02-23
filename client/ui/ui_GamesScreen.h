/********************************************************************************
** Form generated from reading UI file 'GamesScreen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESSCREEN_H
#define UI_GAMESSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GamesScreen
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_4;
    QTableWidget *dataTable;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *createButton;
    QPushButton *refreshButton;
    QPushButton *joinButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *GamesScreen)
    {
        if (GamesScreen->objectName().isEmpty())
            GamesScreen->setObjectName(QString::fromUtf8("GamesScreen"));
        GamesScreen->resize(716, 537);
        gridLayout = new QGridLayout(GamesScreen);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 2, 1, 1);

        dataTable = new QTableWidget(GamesScreen);
        dataTable->setObjectName(QString::fromUtf8("dataTable"));

        gridLayout->addWidget(dataTable, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        createButton = new QPushButton(GamesScreen);
        createButton->setObjectName(QString::fromUtf8("createButton"));

        horizontalLayout_2->addWidget(createButton);

        refreshButton = new QPushButton(GamesScreen);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));

        horizontalLayout_2->addWidget(refreshButton);

        joinButton = new QPushButton(GamesScreen);
        joinButton->setObjectName(QString::fromUtf8("joinButton"));

        horizontalLayout_2->addWidget(joinButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_2, 3, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 4, 1, 1, 1);


        retranslateUi(GamesScreen);

        QMetaObject::connectSlotsByName(GamesScreen);
    } // setupUi

    void retranslateUi(QWidget *GamesScreen)
    {
        GamesScreen->setWindowTitle(QApplication::translate("GamesScreen", "Form", nullptr));
        createButton->setText(QApplication::translate("GamesScreen", "Create", nullptr));
        refreshButton->setText(QApplication::translate("GamesScreen", "Refresh", nullptr));
        joinButton->setText(QApplication::translate("GamesScreen", "Join", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GamesScreen: public Ui_GamesScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESSCREEN_H
