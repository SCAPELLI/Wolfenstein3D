#ifndef EDITOR_TILE_H
#define EDITOR_TILE_H

#include <QWidget>
#include <QtWidgets/QGraphicsItem>
#include "Coordinate.h"
#include "Texture.h"

class Tile : public QGraphicsPixmapItem {
    private:
        Coordinate coordinate;
        Texture texture;

    public:
        Tile(QWidget *parent = 0, size_t xInBits = 0, size_t yInBits = 0, Texture texture = Texture("../sprites/texture0.png"));
        ~Tile();
        void changeImage();
        Coordinate getCoordinate();

};

#endif //EDITOR_TILE_H
