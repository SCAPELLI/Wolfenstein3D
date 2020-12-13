#ifndef EDITOR_TILEMAP_H
#define EDITOR_TILEMAP_H

#include <QWidget>
#include <QtWidgets/QGraphicsView>
#include "Tile.h"
#include "Coordinate.h"

class Tilemap : public QGraphicsView {
    private:
        QGraphicsScene *scene;
        size_t rows;
        size_t columns;

        std::map<Coordinate, Tile*> tiles;


    Tile *tile;

    public:
        Tilemap(QWidget *parent = 0);
        ~Tilemap();
        void setMapSize(size_t rows, size_t columns);

    private:
        void setGrid();

    protected:
        void mousePressEvent(QMouseEvent *event) override;
};


#endif //EDITOR_TILEMAP_H
