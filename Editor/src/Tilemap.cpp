#include <QtWidgets/QLabel>
#include <iostream>
#include "Tilemap.h"
#include <QMouseEvent>

#define BITS 32

Tilemap::Tilemap(QWidget *parent) {
    this->scene = new TilemapScene();
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
    delete this->scene;
}

void Tilemap::setMapSize(size_t rows, size_t columns) {
    this->rows = rows;
    this->columns = columns;
    this->resize(this->rows * BITS, this->columns * BITS);
    this->scene->setMapSize(rows, columns);
}
