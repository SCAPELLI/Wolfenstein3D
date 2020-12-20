#include "TilemapScene.h"
#include "DrawMode.h"
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <EraseMode.h>

#define BITS 32

TilemapScene::TilemapScene(EditorScreen *editorScreen)
    : editorScreen(editorScreen) {
    this->rows = 0;
    this->columns = 0;
    DrawMode *drawMode = new DrawMode(this);
    this->mode = drawMode;

}

TilemapScene::~TilemapScene() {
    /*
     Por la documentacion, QGraphicsScene tiene el ownership de los objetos
     que se le agregan y cuando se llama al destructor de QGraphicsScene se
     aplica delete a todos sus elementos.
     */
    delete this->mode;
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
    QGraphicsItem *item = this->itemAt(event->scenePos(), QTransform());
    std::cout << "Coordenads en el mapa: (" << event->scenePos().x() << ", " << event->scenePos().y() << ")\n";

    this->mode->executeClickResponse(coordinate, item);
}

void TilemapScene::changeToDrawMode() {
    delete this->mode;
    DrawMode *drawMode = new DrawMode(this);
    this->mode = drawMode;
}

void TilemapScene::changeToEraseMode() {
    delete this->mode;
    EraseMode *eraseMode = new EraseMode(this);
    this->mode = eraseMode;
}

void TilemapScene::draw(Coordinate coordinate, QGraphicsItem *item) {
    if (item) {
        this->removeItem(item);
        delete item;
        this->tiles.erase(coordinate);
    }
    Tile *tile = new Tile(0, coordinate, this->editorScreen->getCurrentTexture());
    this->tiles[coordinate] = tile;
    this->addItem(tile);
    QList<QGraphicsItem*> list = this->items();
    std::cout << "DRAW cantidad en el map: " << this->tiles.size() << "\n";
    std::cout << "DRAW cantidad en el scene: " << list.size() << "\n";
    std::cout << "Coordenadas iniciales: (" << coordinate.get_x() << ", " << coordinate.get_y() << ")\n";
    for (auto i = this->tiles.begin(); i != this->tiles.end(); i++) {
        Coordinate coor = i->first;
        std::cout << "Coordenadas en el map: (" << coor.get_x() << ", " << coor.get_y() << ")\n";
    }
    std::cout << "\n";
}

void TilemapScene::erase(Coordinate coordinate, QGraphicsItem *item) {
    QGraphicsLineItem *line = qgraphicsitem_cast<QGraphicsLineItem*>(item);
    if (item && !line) {
        this->removeItem(item);
        delete item;
        this->tiles.erase(coordinate);
    }
    QList<QGraphicsItem*> list = this->items();
    std::cout << "ERASE cantidad en el map: " << this->tiles.size() << "\n";
    std::cout << "ERASE cantidad en el scene: " << list.size() << "\n";
    std::cout << "Coordenadas iniciales: (" << coordinate.get_x() << ", " << coordinate.get_y() << ")\n";
    for (auto i = this->tiles.begin(); i != this->tiles.end(); i++) {
        Coordinate coor = i->first;
        std::cout << "Coordenadas en el map: (" << coor.get_x() << ", " << coor.get_y() << ")\n";
    }
    std::cout << "\n";
}