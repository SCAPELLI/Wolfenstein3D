#ifndef EDITOR_TEXTURE_H
#define EDITOR_TEXTURE_H

#include <string>
#include <QtCore/QString>

class Texture {
    private:
        QString texturePath;
        QString type;
        int id;

    public:
        Texture(const QString &texturePath, const QString &textureType, int id);
        ~Texture();
        QString getTexturePath();
        QString getTextureType();
        int getId();
};

#endif //EDITOR_TEXTURE_H
