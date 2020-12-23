#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include "SpriteFileManager.h"

SpriteFileManager::SpriteFileManager() {}

SpriteFileManager::~SpriteFileManager() {}

std::map<std::string, std::map<int, std::string>> SpriteFileManager::createMapFromTextureFile() {
    std::map <std::string,std::map <int, std::string>> sprites;

    YAML::Node node = YAML::LoadFile("../sprites/sprites.yaml");

    for (auto categoryIt = node.begin(); categoryIt != node.end(); ++categoryIt) {
        YAML::Node category = categoryIt->second;
        std::map<int, std::string> elemMap;
        for (auto elemIt = category.begin(); elemIt != category.end(); elemIt++) {
            elemMap[elemIt->first.as<int>()] = elemIt->second.as<std::string>();
        }
        sprites[categoryIt->first.as<std::string>()] = elemMap;
    }
    return sprites;
}