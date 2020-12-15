#include "TilemapScene.h"
#include <QGraphicsSceneMouseEvent>
#include <iostream>

#define BITS 32

TilemapScene::TilemapScene(EditorScreen *editorScreen)
    : editorScreen(editorScreen) {
    this->rows = 0;
    this->columns = 0;
}

TilemapScene::~TilemapScene() {
    /*
     Por la documentacion, QGraphicsScene tiene el ownership de los objetos
     que se le agregan y cuando se llama al destructor de QGraphicsScene se
     aplica delete a todos sus elementos.
     */
}

void TilemapScene::setMapSize(size_t rows, size_t columns) {
    this->rows = rows;
    this->columns = columns;
    this->setGrid();
}

void TilemapScene::setGrid() {
    int x, y;

    for (x = 0; x < this->rows * BITS; x+=BITS) {
        this->addLine(x, 0, x, this->columns * BITS, QPen(Qt::black));
        if (x + BITS - 1 < this->rows * BITS) {
            this->addLine(x + BITS - 1, 0, x + BITS - 1, this->columns * BITS, QPen(Qt::black));
        }
    }

    for (y = 0; y < this->columns * BITS; y+=BITS) {
        this->addLine(0, y, this->rows * BITS - 1, y, QPen(Qt::black));
        if (y + BITS - 1 < this->columns * BITS) {
            this->addLine(0, y + BITS - 1, this->rows * BITS - 1, y + BITS - 1, QPen(Qt::black));
        }
    }
}

void TilemapScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->scenePos().x() < 0 || event->scenePos().y() < 0 ||
    event->scenePos().x() >= this->rows * BITS || event->scenePos().y() >= this->columns * BITS) {
        event->ignore();
        return;
    }

    Coordinate coordinate(event->scenePos().x(), event->scenePos().y());
    Tile *tile = new Tile(0, coordinate, this->editorScreen->getCurrentTexture());
    this->tiles.insert(std::pair<Coordinate, Tile*>(
            tile->getCoordinate(),
            tile));
    this->addItem(tile);
}