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
        std::string fileName;
        Texture currentTexture;
        SpriteTabs *spriteTabs;

    public:
        EditorScreen(QWidget *parent = 0, ScreenManager *screenManager = NULL);
        ~EditorScreen();
        void connectEvents();
        void newMap();
        void saveMap();
        void openMap();
        void changeCurrentTexture(Texture newTexture);
        Texture getCurrentTexture();
        void changeToDrawMode();
        void changeToEraseMode();
        void createMapYalm();

};


#endif //EDITOR_EDITORSCREEN_H
