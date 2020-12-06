#ifndef EDITOR_TEXTURELIST_H
#define EDITOR_TEXTURELIST_H

#include <QtWidgets/QListWidget>

class TextureList : QListWidget {

    private:
        QListWidget *textureList;

    public:
        TextureList(QWidget *parent = 0);
        ~TextureList();
        void addTexture(std::string texturePath);

};


#endif //EDITOR_TEXTURELIST_H
