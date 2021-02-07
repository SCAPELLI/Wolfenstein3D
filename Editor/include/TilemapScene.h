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
        EditorScreen *editorScreen;
        Mode* mode;
        std::vector<std::vector<int>> vector;

    public:
        TilemapScene(EditorScreen *editorScreen, size_t rows, size_t columns);
        ~TilemapScene();
        void setMapSize(size_t rows, size_t columns);
        void draw(Coordinate coordinate, QGraphicsItem *item);
        void erase(Coordinate coordinate, QGraphicsItem *item);
        void changeToDrawMode();
        void changeToEraseMode();
        bool isAValidPosition(QGraphicsSceneMouseEvent *event);
        std::vector<std::vector<int>> getMapMatrix();
        void setMapMatrix(std::vector<std::vector<int>> matrix);

protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    private:
        void setGrid();

};


#endif //EDITOR_TILEMAPSCENE_H
