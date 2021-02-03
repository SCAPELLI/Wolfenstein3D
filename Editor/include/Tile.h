#ifndef EDITOR_TILE_H
#define EDITOR_TILE_H

#include "Coordinate.h"
#include "Texture.h"

#include <QWidget>
#include <QtWidgets/QGraphicsItem>

class Tile : public QGraphicsPixmapItem {
    private:
        Coordinate coordinate;
        Texture texture;

    public:
        Tile(QWidget *parent = 0,
             Coordinate coordinate = Coordinate(0, 0),
             Texture texture = Texture("../sprites/sprite100.png", "wall", 100));
        ~Tile();
};

#endif //EDITOR_TILE_H
