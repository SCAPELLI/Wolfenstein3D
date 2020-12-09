#include <QtWidgets/QLabel>
#include <iostream>
#include "Tilemap.h"
#include <QMouseEvent>
#include <Tile.h>

#define ROWS 10
#define COLUMNS 15
#define BITS 32

Tilemap::Tilemap(QWidget *parent) {
    this->resize(ROWS * BITS, COLUMNS * BITS);
    this->scene = new QGraphicsScene;
    int x, y;

    this->setGrid();
    //QLabel *uwu = new QLabel("holis");
    //this->scene->addWidget(uwu);

    Tile *tile = new Tile();
    this->scene->addItem(tile);

    this->setScene(this->scene);
    this->show();
}

Tilemap::~Tilemap() {
    delete this->scene;
}

void Tilemap::setGrid() {
    int x, y;

    for (x = 0; x < ROWS * BITS; x+=BITS) {
        this->scene->addLine(x, 0, x, COLUMNS * BITS, QPen(Qt::black));
        if (x + BITS - 1 < ROWS * BITS) {
            this->scene->addLine(x + BITS - 1, 0, x + BITS - 1, COLUMNS * BITS, QPen(Qt::black));
        }
    }

    for (y = 0; y < COLUMNS * BITS; y+=BITS) {
        this->scene->addLine(0, y, ROWS * BITS - 1, y, QPen(Qt::black));
        if (y + BITS - 1 < COLUMNS * BITS) {
            this->scene->addLine(0, y + BITS - 1, ROWS * BITS - 1, y + BITS - 1, QPen(Qt::black));
        }
    }
}

void Tilemap::mousePressEvent(QMouseEvent *event) {
    /*
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child) {
        return;
    } else {
        QGraphicsItem *item = itemAt(event->pos());
        this->scene->removeItem(item);
    }
    std::cout << "a child";
*/
    std::cout << "a child";

}