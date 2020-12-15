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
             Texture texture = Texture("../sprites/texture0.png"));
        ~Tile();
        Coordinate getCoordinate();
};

#endif //EDITOR_TILE_H
