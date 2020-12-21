#ifndef EDITOR_TEXTURELIST_H
#define EDITOR_TEXTURELIST_H

#include <QtWidgets/QListWidget>
#include "Texture.h"

class EditorScreen;

class TextureList : public QListWidget {

    private:
        EditorScreen *editorScreen;
        std::vector<Texture> textures;

    public:
        TextureList(QWidget *parent = 0, EditorScreen *editorScreen = NULL);
        ~TextureList();
        void addTexture(std::string texturePath);

    private:
       void mousePressEvent(QMouseEvent *event) override;

};

#endif //EDITOR_TEXTURELIST_H
