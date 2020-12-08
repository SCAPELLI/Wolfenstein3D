#include "Prueba.h"

Prueba::Prueba(QWidget *parent)
    : QWidget(parent){
    this->scrollArea = new QScrollArea();
    this->scrollArea->setWidget(this);
    this->scrollArea->setBackgroundRole(QPalette::Dark);

}