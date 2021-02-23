/********************************************************************************
** Form generated from reading UI file 'EditorScreen.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORSCREEN_H
#define UI_EDITORSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditorScreen
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *buttonLayout;
    QPushButton *newButton;
    QPushButton *openButton;
    QPushButton *saveButton;
    QHBoxLayout *horizontalLayout;
    QPushButton *drawButton;
    QPushButton *eraseButton;
    QVBoxLayout *tilemapLayout;
    QGraphicsView *tilemap;
    QVBoxLayout *textureListLayout;

    void setupUi(QMainWindow *EditorScreen)
    {
        if (EditorScreen->objectName().isEmpty())
            EditorScreen->setObjectName(QString::fromUtf8("EditorScreen"));
        EditorScreen->resize(727, 552);
        EditorScreen->setStyleSheet(QString::fromUtf8("background: rgb(137, 0, 0)"));
        centralwidget = new QWidget(EditorScreen);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonLayout = new QVBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        newButton = new QPushButton(centralwidget);
        newButton->setObjectName(QString::fromUtf8("newButton"));

        buttonLayout->addWidget(newButton);

        openButton = new QPushButton(centralwidget);
        openButton->setObjectName(QString::fromUtf8("openButton"));

        buttonLayout->addWidget(openButton);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        buttonLayout->addWidget(saveButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        drawButton = new QPushButton(centralwidget);
        drawButton->setObjectName(QString::fromUtf8("drawButton"));

        horizontalLayout->addWidget(drawButton);

        eraseButton = new QPushButton(centralwidget);
        eraseButton->setObjectName(QString::fromUtf8("eraseButton"));

        horizontalLayout->addWidget(eraseButton);


        buttonLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(buttonLayout, 0, 2, 1, 1);

        tilemapLayout = new QVBoxLayout();
        tilemapLayout->setObjectName(QString::fromUtf8("tilemapLayout"));
        tilemap = new QGraphicsView(centralwidget);
        tilemap->setObjectName(QString::fromUtf8("tilemap"));
        tilemap->setStyleSheet(QString::fromUtf8("background: rgb(88, 0, 0)"));

        tilemapLayout->addWidget(tilemap);


        gridLayout->addLayout(tilemapLayout, 0, 0, 3, 1);

        textureListLayout = new QVBoxLayout();
        textureListLayout->setObjectName(QString::fromUtf8("textureListLayout"));
        textureListLayout->setSizeConstraint(QLayout::SetDefaultConstraint);

        gridLayout->addLayout(textureListLayout, 1, 1, 2, 3);

        EditorScreen->setCentralWidget(centralwidget);

        retranslateUi(EditorScreen);

        QMetaObject::connectSlotsByName(EditorScreen);
    } // setupUi

    void retranslateUi(QMainWindow *EditorScreen)
    {
        EditorScreen->setWindowTitle(QApplication::translate("EditorScreen", "MainWindow", nullptr));
        newButton->setText(QApplication::translate("EditorScreen", "New", nullptr));
        openButton->setText(QApplication::translate("EditorScreen", "Open", nullptr));
        saveButton->setText(QApplication::translate("EditorScreen", "Save", nullptr));
        drawButton->setText(QApplication::translate("EditorScreen", "Draw", nullptr));
        eraseButton->setText(QApplication::translate("EditorScreen", "Erase", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditorScreen: public Ui_EditorScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORSCREEN_H
