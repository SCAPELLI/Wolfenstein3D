/********************************************************************************
** Form generated from reading UI file 'ScoreWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCOREWINDOW_H
#define UI_SCOREWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScoreWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTableWidget *scoreTable;
    QHBoxLayout *horizontalLayout_2;
    QLabel *nameLabel;
    QLabel *killsLabel;
    QLabel *bulletsLabel;
    QLabel *scoreLabel;
    QLabel *titleLabel;

    void setupUi(QMainWindow *ScoreWindow)
    {
        if (ScoreWindow->objectName().isEmpty())
            ScoreWindow->setObjectName(QString::fromUtf8("ScoreWindow"));
        ScoreWindow->resize(800, 600);
        ScoreWindow->setStyleSheet(QString::fromUtf8("background: rgb(136, 0, 0)"));
        centralwidget = new QWidget(ScoreWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scoreTable = new QTableWidget(centralwidget);
        scoreTable->setObjectName(QString::fromUtf8("scoreTable"));
        scoreTable->setStyleSheet(QString::fromUtf8("background: rgb(136, 0, 0)"));
        scoreTable->setGridStyle(Qt::NoPen);

        gridLayout->addWidget(scoreTable, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        nameLabel = new QLabel(centralwidget);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setStyleSheet(QString::fromUtf8("color: rgb(190, 193, 3)"));
        nameLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(nameLabel);

        killsLabel = new QLabel(centralwidget);
        killsLabel->setObjectName(QString::fromUtf8("killsLabel"));
        killsLabel->setStyleSheet(QString::fromUtf8("color: rgb(190, 193, 3)"));
        killsLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(killsLabel);

        bulletsLabel = new QLabel(centralwidget);
        bulletsLabel->setObjectName(QString::fromUtf8("bulletsLabel"));
        bulletsLabel->setStyleSheet(QString::fromUtf8("color: rgb(190, 193, 3)"));
        bulletsLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(bulletsLabel);

        scoreLabel = new QLabel(centralwidget);
        scoreLabel->setObjectName(QString::fromUtf8("scoreLabel"));
        scoreLabel->setStyleSheet(QString::fromUtf8("color: rgb(190, 193, 3)"));
        scoreLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(scoreLabel);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(titleLabel, 0, 0, 1, 1);

        ScoreWindow->setCentralWidget(centralwidget);

        retranslateUi(ScoreWindow);

        QMetaObject::connectSlotsByName(ScoreWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ScoreWindow)
    {
        ScoreWindow->setWindowTitle(QApplication::translate("ScoreWindow", "MainWindow", nullptr));
        nameLabel->setText(QApplication::translate("ScoreWindow", "name", nullptr));
        killsLabel->setText(QApplication::translate("ScoreWindow", "kills", nullptr));
        bulletsLabel->setText(QApplication::translate("ScoreWindow", "bullets", nullptr));
        scoreLabel->setText(QApplication::translate("ScoreWindow", "score", nullptr));
        titleLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ScoreWindow: public Ui_ScoreWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCOREWINDOW_H
