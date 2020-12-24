#ifndef EDITOR_SPRITEFILEMANAGER_H
#define EDITOR_SPRITEFILEMANAGER_H

#include <map>

class SpriteFileManager {
    public:
        SpriteFileManager();
        ~SpriteFileManager();
        std::map<std::string, std::map<int, std::string>> createMapFromTextureFile();
};

#endif //EDITOR_SPRITEFILEMANAGER_H
