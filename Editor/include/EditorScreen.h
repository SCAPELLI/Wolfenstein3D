#ifndef EDITOR_EDITORSCREEN_H
#define EDITOR_EDITORSCREEN_H

#include "ScreenManager.h"
#include "Texture.h"
#include "SpriteTabs.h"
#include <QMainWindow>
#include <QWidget>
#include <fstream>
#include <QtWidgets/QGraphicsView>

class TextureList;
class TilemapScene;

namespace Ui {
    class EditorScreen;
}

class EditorScreen : public QMainWindow {
    Q_OBJECT;

    private:
        Ui::EditorScreen *ui;
        ScreenManager *screenManager;
        TilemapScene *tilemapScene;
        std::ofstream mapFile;
        Texture currentTexture;
        SpriteTabs *spriteTabs;

    public:
        EditorScreen(QWidget *parent = 0, ScreenManager *screenManager = NULL);
        ~EditorScreen();
        void setMapSize(size_t rows, size_t columns);
        void connectEvents();
        void saveMap();
        void changeCurrentTexture(Texture newTexture);
        Texture getCurrentTexture();
        void changeToDrawMode();
        void changeToEraseMode();

};


#endif //EDITOR_EDITORSCREEN_H
