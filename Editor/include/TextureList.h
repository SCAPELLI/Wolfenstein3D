#ifndef EDITOR_TEXTURELIST_H
#define EDITOR_TEXTURELIST_H

#include <QtWidgets/QListWidget>
#include "Texture.h"
#include <map>

class SpriteTabs;

class TextureList : public QListWidget {

    private:
        SpriteTabs *spriteTabs;
        std::vector<Texture> textures;

    public:
        TextureList(QWidget *parent = 0, SpriteTabs *spriteTabs = NULL);
        ~TextureList();
        void addTexture(const std::string &texturePath, const std::string &textureType, int id);
        void setSpriteList(std::map<int, std::string> &spriteMap);

    private:
       void mousePressEvent(QMouseEvent *event) override;
       void setStyle();

};

#endif //EDITOR_TEXTURELIST_H
