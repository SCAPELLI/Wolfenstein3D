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
        std::ofstream mapFilePath;

    public:
        EditorScene(QWidget *parent = 0, ScreenManager *screenManager = NULL);
        ~EditorScene();
        void setMapSize(size_t rows, size_t columns);

};


#endif //EDITOR_EDITORSCENE_H
