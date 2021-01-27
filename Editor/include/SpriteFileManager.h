#ifndef EDITOR_SPRITEFILEMANAGER_H
#define EDITOR_SPRITEFILEMANAGER_H

#include <map>

class SpriteFileManager {
    public:
        SpriteFileManager();
        ~SpriteFileManager();
        std::map<int, std::string> createMapFromTextureFileWithoutValues(std::string key);
        std::map<int, std::string> createMapFromTextureFileWithValues(std::string key);
};

#endif //EDITOR_SPRITEFILEMANAGER_H
