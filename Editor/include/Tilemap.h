#ifndef EDITOR_TILEMAP_H
#define EDITOR_TILEMAP_H

#include "Tile.h"
#include "Coordinate.h"
#include "TilemapScene.h"

#include <QWidget>
#include <QtWidgets/QGraphicsView>
#include <QMouseEvent>

class EditorScreen;

class Tilemap : public QGraphicsView {
    private:
        TilemapScene *scene;
        size_t rows;
        size_t columns;
        EditorScreen *editorScreen;

    public:
        Tilemap(QWidget *parent = 0, EditorScreen *editorScreen = NULL);
        ~Tilemap();
        void setMapSize(size_t rows, size_t columns);
};

#endif //EDITOR_TILEMAP_H
