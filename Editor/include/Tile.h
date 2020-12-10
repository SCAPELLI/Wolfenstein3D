#ifndef EDITOR_TILE_H
#define EDITOR_TILE_H

#include <QWidget>
#include <QtWidgets/QGraphicsItem>

class Tile : public QGraphicsPixmapItem {

    public:
        Tile(QWidget *parent = 0);

};

#endif //EDITOR_TILE_H
