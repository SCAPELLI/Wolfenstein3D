#ifndef EDITOR_TILEMAPSCENE_H
#define EDITOR_TILEMAPSCENE_H

#include <QtWidgets/QGraphicsScene>
#include <Coordinate.h>
#include <Tile.h>

class TilemapScene : public QGraphicsScene {
    private:
        size_t rows;
        size_t columns;
        std::map<Coordinate, Tile*> tiles;

    public:
        TilemapScene();
        ~TilemapScene();
        void setMapSize(size_t rows, size_t columns);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    private:
        void setGrid();

};


#endif //EDITOR_TILEMAPSCENE_H
