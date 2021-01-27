#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include "SpriteFileManager.h"

SpriteFileManager::SpriteFileManager() {}

SpriteFileManager::~SpriteFileManager() {}

std::map<int, std::string> SpriteFileManager::createMapFromTextureFileWithoutValues(std::string key) {
    YAML::Node node = YAML::LoadFile("../sprites/sprites.yaml");
    YAML::Node category = node[key];

    std::map<int, std::string> map;

    for (auto categoryIt = category.begin(); categoryIt != category.end(); ++categoryIt) {
        map[categoryIt->first.as<int>()] = categoryIt->second.as<std::string>();
    }

    return map;
}

std::map<int, std::string> SpriteFileManager::createMapFromTextureFileWithValues(std::string key) {
    YAML::Node node = YAML::LoadFile("../sprites/sprites.yaml");
    YAML::Node category = node[key];

    std::map<int, std::string> map;

    for (auto categoryIt = category.begin(); categoryIt != category.end(); ++categoryIt) {
        map[categoryIt->first.as<int>()] = categoryIt->second["type"].as<std::string>();
    }

    return map;
}