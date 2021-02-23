#include "Tile.h"

#define BITS 32

Tile::Tile(QWidget *parent, Coordinate coordinate, Texture texture)
    : coordinate(coordinate), texture(texture){
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    QString texturePath = texture.getTexturePath();
    QPixmap aux(texturePath);
    QPixmap auxScaled = aux.scaled(BITS, BITS);
    this->setPixmap(auxScaled);
    this->setPos(this->coordinate.get_x() * BITS,
                 this->coordinate.get_y() * BITS);
}

Tile::~Tile() {}
