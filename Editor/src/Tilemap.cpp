#include <QtWidgets/QLabel>
#include <iostream>
#include "Tilemap.h"
#include <QMouseEvent>

#define BITS 32

Tilemap::Tilemap(QWidget *parent) {
    this->scene = new QGraphicsScene;
    this->rows = 0;
    this->columns = 0;
    //this->resize(this->rows * BITS, this->columns * BITS);

    //this->setGrid();
    //QLabel *uwu = new QLabel("holis");
    //this->scene->addWidget(uwu);

    //this->tile = new Tile();
    //this->scene->addItem(this->tile);

    //Coordinate coordinate(0,0);
    //this->tiles.insert(std::pair<Coordinate, Tile*>(coordinate,
    //                                                new Tile()));
    //this->scene->addItem(this->tiles[coordinate]);

    this->setScene(this->scene);
    this->show();
}

Tilemap::~Tilemap() {
    QList<QGraphicsItem*> sceneItems = this->scene->items();
    std::cout << sceneItems.count();
    if (sceneItems.count() > 0) {
        int i;
        for(i = 0; i < sceneItems.count(); i++) {
            QGraphicsItem *item = sceneItems[i];
            delete item;
        }
    }
    delete this->scene;
}

void Tilemap::setMapSize(size_t rows, size_t columns) {
    this->rows = rows;
    this->columns = columns;
    this->resize(this->rows * BITS, this->columns * BITS);
    setGrid();
}

void Tilemap::setGrid() {
    int x, y;

    for (x = 0; x < this->rows * BITS; x+=BITS) {
        this->scene->addLine(x, 0, x, this->columns * BITS, QPen(Qt::black));
        if (x + BITS - 1 < this->rows * BITS) {
            this->scene->addLine(x + BITS - 1, 0, x + BITS - 1, this->columns * BITS, QPen(Qt::black));
        }
    }

    for (y = 0; y < this->columns * BITS; y+=BITS) {
        this->scene->addLine(0, y, this->rows * BITS - 1, y, QPen(Qt::black));
        if (y + BITS - 1 < this->columns * BITS) {
            this->scene->addLine(0, y + BITS - 1, this->rows * BITS - 1, y + BITS - 1, QPen(Qt::black));
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

    /*
    QGraphicsItem *item = itemAt(event->pos());
    if (item) {
        std::cout << "an item\n";
        this->tile->changeImage();
    } else {
        std::cout << "nothing\n";
    }
     */

    /*
    QGraphicsPixmapItem *item =
            dynamic_cast<QGraphicsPixmapItem*>(itemAt(event->pos()));
    if (item) {
        this->scene->removeItem(item);
        delete this->tile;
    }
*/

    Tile *tile = new Tile(0, event->x(), event->y());
    std::cout << "Event->x" << event->x() << '\n';
    std::cout << "Event->y" << event->y() << '\n';
    this->tiles.insert(std::pair<Coordinate, Tile*>(
            tile->getCoordinate(),
            tile));
    this->scene->addItem(tile);
}