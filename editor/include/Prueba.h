//
// Created by nicole on 8/12/20.
//

#ifndef EDITOR_PRUEBA_H
#define EDITOR_PRUEBA_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>

class Prueba : QWidget {

    private:
        QScrollArea *scrollArea;
        QFrame *grid;

    public:
        Prueba(QWidget *parent = 0);
};


#endif //EDITOR_PRUEBA_H
