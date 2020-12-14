#ifndef EDITOR_TILEMAP_H
#define EDITOR_TILEMAP_H

#include <QWidget>
#include <QtWidgets/QGraphicsView>
#include "Tile.h"
#include "Coordinate.h"
#include "../src/TilemapScene.h"

class Tilemap : public QGraphicsView {
    private:
        TilemapScene *scene;
        size_t rows;
        size_t columns;
        std::map<Coordinate, Tile*> tiles;

    public:
        Tilemap(QWidget *parent = 0);
        ~Tilemap();
        void setMapSize(size_t rows, size_t columns);

};

#endif //EDITOR_TILEMAP_H
