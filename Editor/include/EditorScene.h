#ifndef EDITOR_EDITORSCENE_H
#define EDITOR_EDITORSCENE_H

#include "SceneManager.h"
#include "TextureList.h"
#include "Tilemap.h"
#include <QMainWindow>
#include <QWidget>

namespace Ui {
    class EditorScene;
}

class EditorScene : public QMainWindow {
    Q_OBJECT;

    private:
        Ui::EditorScene *ui;
        SceneManager *sceneManager;
        TextureList *textureList;
        Tilemap *tilemap;

    public:
        EditorScene(QWidget *parent = 0, SceneManager *sceneManager = NULL);
        ~EditorScene();

};


#endif //EDITOR_EDITORSCENE_H
