#ifndef EDITOR_SPRITETABS_H
#define EDITOR_SPRITETABS_H

#include <TextureList.h>

#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>

class EditorScreen;

class SpriteTabs: public QTabWidget {
    private:
        EditorScreen *editorScreen;
        TextureList *textureList;
        TextureList *itemsList;
        TextureList *decorationsList;

    public:
        SpriteTabs(QWidget *parent = 0, EditorScreen *editorScreen = NULL);
        ~SpriteTabs();
        void changeCurrentTexture(Texture texture);
};


#endif //EDITOR_SPRITETABS_H
