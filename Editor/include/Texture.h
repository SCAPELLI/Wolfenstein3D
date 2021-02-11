#ifndef EDITOR_TEXTURE_H
#define EDITOR_TEXTURE_H

#include <string>
#include <QtCore/QString>

class Texture {
    private:
        QString texturePath;
        int id;

    public:
        Texture(const QString &texturePath, int id);
        ~Texture();
        QString getTexturePath();
        int getId();
};

#endif //EDITOR_TEXTURE_H
