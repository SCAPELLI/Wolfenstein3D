#ifndef EDITOR_TEXTURE_H
#define EDITOR_TEXTURE_H

#include <string>
#include <QtCore/QString>

class Texture {
    private:
        QString texturePath;

    public:
        Texture(const QString &texturePath);
        ~Texture();
        QString getTexturePath();
};


#endif //EDITOR_TEXTURE_H
