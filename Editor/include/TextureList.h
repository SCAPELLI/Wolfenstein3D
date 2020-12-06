#ifndef EDITOR_TEXTURELIST_H
#define EDITOR_TEXTURELIST_H

#include <QtWidgets/QListWidget>

class TextureList {

    private:
        QListWidget *textureList;

    public:
        TextureList(QListWidget *textureList);
        ~TextureList();
        void addTexture(std::string texturePath);

};


#endif //EDITOR_TEXTURELIST_H
