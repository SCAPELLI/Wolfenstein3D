#ifndef EDITOR_EDITORSCENE_H
#define EDITOR_EDITORSCENE_H

#include "ScreenManager.h"
#include "TextureList.h"
#include "Tilemap.h"
#include <QMainWindow>
#include <QWidget>
#include <fstream>

namespace Ui {
    class EditorScene;
}

class EditorScene : public QMainWindow {
    Q_OBJECT;

    private:
        Ui::EditorScene *ui;
        ScreenManager *screenManager;
        TextureList *textureList;
        Tilemap *tilemap;
        std::ofstream mapFile;

    public:
        EditorScene(QWidget *parent = 0, ScreenManager *screenManager = NULL);
        ~EditorScene();
        void setMapSize(size_t rows, size_t columns);
        void connectEvents();
        void saveMap();

};


#endif //EDITOR_EDITORSCENE_H
