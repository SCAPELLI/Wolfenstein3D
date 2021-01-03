#ifndef EDITOR_TEXTURE_H
#define EDITOR_TEXTURE_H

#include <string>
#include <QtCore/QString>

class Texture {
    private:
        QString texturePath;
        QString type;

    public:
        Texture(const QString &texturePath, const QString &textureType);
        ~Texture();
        QString getTexturePath();
        QString getTextureType();
};

#endif //EDITOR_TEXTURE_H
