#ifndef EDITOR_SPRITEFILEMANAGER_H
#define EDITOR_SPRITEFILEMANAGER_H

#include <map>
#include <vector>

class SpriteFileManager {
    public:
        SpriteFileManager();
        ~SpriteFileManager();
        std::map<int, std::string> createMapFromTextureFileWithoutValues(const std::string &key);
        std::map<int, std::string> createMapFromTextureFileWithValues(const std::string &key);
        bool mapHasValidIds(std::vector<std::vector<int>> &matrix);
};

#endif //EDITOR_SPRITEFILEMANAGER_H
