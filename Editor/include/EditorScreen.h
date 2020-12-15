#ifndef EDITOR_EDITORSCREEN_H
#define EDITOR_EDITORSCREEN_H

#include "ScreenManager.h"
#include "Texture.h"
#include <QMainWindow>
#include <QWidget>
#include <fstream>

class TextureList;
class Tilemap;

namespace Ui {
    class EditorScreen;
}

class EditorScreen : public QMainWindow {
    Q_OBJECT;

    private:
        Ui::EditorScreen *ui;
        ScreenManager *screenManager;
        TextureList *textureList;
        Tilemap *tilemap;
        std::ofstream mapFile;
        Texture currentTexture;

    public:
        EditorScreen(QWidget *parent = 0, ScreenManager *screenManager = NULL);
        ~EditorScreen();
        void setMapSize(size_t rows, size_t columns);
        void connectEvents();
        void saveMap();
        void changeCurrentTexture(Texture newTexture);
        Texture getCurrentTexture();

};


#endif //EDITOR_EDITORSCREEN_H
