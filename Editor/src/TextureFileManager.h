#ifndef EDITOR_TEXTUREFILEMANAGER_H
#define EDITOR_TEXTUREFILEMANAGER_H

class TextureFileManager {
    public:
        TextureFileManager();
        ~TextureFileManager();
        /*
         * Devuelve un mapa que contiene un mapa de los sprites.
         * Ejemplo:
         * {
         * "items": {0: "food", 1: "key"},
         * "textures": {100: wall, 101: "door"}
         * }
         */
        std::map<std::string, std::map<int, std::string>> createMapFromTextureFile();
};

#endif //EDITOR_TEXTUREFILEMANAGER_H
