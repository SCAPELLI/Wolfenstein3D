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
    this->vector = std::vector<std::vector<int>>(rows, std::vector<int> (columns,0));
    this->setGrid();
}

void TilemapScene::setGrid() {
    int x, y;

    for (x = 0; x < this->columns * BITS; x+=BITS) {
        this->addLine(x, 0, x, this->rows * BITS, QPen(Qt::black));
        if (x + BITS - 1 < this->columns * BITS) {
            this->addLine(x + BITS - 1, 0, x + BITS - 1, this->rows * BITS, QPen(Qt::black));
        }
    }

    for (y = 0; y < this->rows * BITS; y+=BITS) {
        this->addLine(0, y, this->columns * BITS - 1, y, QPen(Qt::black));
        if (y + BITS - 1 < this->rows * BITS) {
            this->addLine(0, y + BITS - 1, this->columns * BITS - 1, y + BITS - 1, QPen(Qt::black));
        }
    }
}

void TilemapScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (!isAValidPosition(event)) {
        event->ignore();
        return;
    }

    Coordinate coordinate(event->scenePos().x(), event->scenePos().y());
    QGraphicsItem *item = this->itemAt(event->scenePos(), QTransform());
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
    int x = coordinate.get_x();
    int y = coordinate.get_y();
    QGraphicsLineItem *line = qgraphicsitem_cast<QGraphicsLineItem*>(item);
    if (item && !line) {
        this->removeItem(item);
        delete item;
    }
    this->vector[y][x] = this->editorScreen->getCurrentTexture().getId();
    for (int i = 0; i != this->vector.size(); i++) {
        std::cout << "[ ";
        for (int j = 0; j != this->vector[i].size(); j++) {
            std::cout << vector[i][j] << ", ";
        }
        std::cout << "]\n";
    }

    Tile *tile = new Tile(0, coordinate, this->editorScreen->getCurrentTexture());
    this->addItem(tile);
    QList<QGraphicsItem*> list = this->items();
    std::cout << "DRAW cantidad en el scene: " << list.size() << "\n";
}

void TilemapScene::erase(Coordinate coordinate, QGraphicsItem *item) {
    int x = coordinate.get_x();
    int y = coordinate.get_y();
    QGraphicsLineItem *line = qgraphicsitem_cast<QGraphicsLineItem*>(item);
    if (item && !line) {
        this->vector[y][x] = 0;
        this->removeItem(item);
        delete item;
    }
    QList<QGraphicsItem*> list = this->items();
    std::cout << "Erase cantidad en el scene: " << list.size() << "\n";
}

bool TilemapScene::isAValidPosition(QGraphicsSceneMouseEvent *event) {
    if (event->scenePos().x() < 0 || event->scenePos().y() < 0 ||
        event->scenePos().x() >= this->columns * BITS || event->scenePos().y() >= this->rows * BITS) {
        return false;
    }
    return true;
}

std::vector<std::vector<int>> TilemapScene::getMapMatrix() {
    return this->vector;
}

void TilemapScene::setMapMatrix(std::vector<std::vector<int>> matrix) {
    this->vector = matrix;
    int row, column;
    for (int row = 0; row != this->vector.size(); row++){
        for (int column = 0; column != this->vector[row].size(); column++) {
            int id = this->vector[row][column];
            if (id != 0) {
                Coordinate coordinate(column * 32, row * 32);
                std::string spritePath = "../sprites/sprite" + std::to_string(this->vector[row][column]) + ".png";
                QString str = QString::fromUtf8(spritePath.c_str());
                Texture texture(str, this->vector[row][column]);
                Tile *tile = new Tile(0, coordinate, texture);
                this->addItem(tile);
            }
        }
    }
}