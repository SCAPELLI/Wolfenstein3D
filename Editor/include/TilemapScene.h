#ifndef EDITOR_TILEMAPSCENE_H
#define EDITOR_TILEMAPSCENE_H

#include <QtWidgets/QGraphicsScene>
#include <Coordinate.h>
#include <Tile.h>
#include "EditorScreen.h"

class Mode;

class TilemapScene : public QGraphicsScene {
    private:
        size_t rows;
        size_t columns;
        std::map<Coordinate, Tile*> tiles;
        EditorScreen *editorScreen;
        Mode* mode;

    public:
        TilemapScene(EditorScreen *editorScreen);
        ~TilemapScene();
        void setMapSize(size_t rows, size_t columns);
        void draw(Coordinate coordinate, QGraphicsItem *item);
        void erase(Coordinate coordinate, QGraphicsItem *item);
        void changeToDrawMode();
        void changeToEraseMode();
        std::map<Coordinate, Tile*> getTiles();

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    private:
        void setGrid();

};


#endif //EDITOR_TILEMAPSCENE_H
