#ifndef EDITOR_TILEMAPSCENE_H
#define EDITOR_TILEMAPSCENE_H

#include <QtWidgets/QGraphicsScene>
#include <Coordinate.h>
#include <Tile.h>
#include "EditorScreen.h"


class TilemapScene : public QGraphicsScene {
    private:
        size_t rows;
        size_t columns;
        std::map<Coordinate, Tile*> tiles;
        EditorScreen *editorScreen;

    public:
        TilemapScene(EditorScreen *editorScreen);
        ~TilemapScene();
        void setMapSize(size_t rows, size_t columns);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    private:
        void setGrid();

};


#endif //EDITOR_TILEMAPSCENE_H
