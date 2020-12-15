#ifndef EDITOR_TEXTURELIST_H
#define EDITOR_TEXTURELIST_H

#include <QtWidgets/QListWidget>

class TextureList : public QListWidget {

    private:

    public:
        TextureList(QWidget *parent = 0);
        ~TextureList();
        void addTexture(std::string texturePath);

    private:
        //void connectEvents();
        void setCurrentTexture();
       void mousePressEvent(QMouseEvent *event) override;
};


#endif //EDITOR_TEXTURELIST_H
