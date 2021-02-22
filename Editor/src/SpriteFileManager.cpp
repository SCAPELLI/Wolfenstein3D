#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include "SpriteFileManager.h"

#define PATH "../sprites/sprites.yaml"
#define WEAPONS_START_AT 50
#define TEXTURES_START_AT 100
#define DECORATIONS_START_AT 200
#define WALKABLE_START_AT 300

SpriteFileManager::SpriteFileManager() {}

SpriteFileManager::~SpriteFileManager() {}

std::map<int, std::string> SpriteFileManager::createMapFromTextureFileWithoutValues(const std::string &key) {
    YAML::Node node = YAML::LoadFile(PATH);
    YAML::Node category = node[key];

    std::map<int, std::string> map;

    for (auto categoryIt = category.begin(); categoryIt != category.end(); ++categoryIt) {
        map[categoryIt->first.as<int>()] = categoryIt->second.as<std::string>();
    }

    return map;
}

std::map<int, std::string> SpriteFileManager::createMapFromTextureFileWithValues(const std::string &key) {
    YAML::Node node = YAML::LoadFile(PATH);
    YAML::Node category = node[key];

    std::map<int, std::string> map;

    for (auto categoryIt = category.begin(); categoryIt != category.end(); ++categoryIt) {
        map[categoryIt->first.as<int>()] = categoryIt->second["type"].as<std::string>();
    }

    return map;
}

bool SpriteFileManager::mapHasValidIds(std::vector<std::vector<int>> &matrix) {
    YAML::Node node = YAML::LoadFile(PATH);
    int items = node["items"].size();
    int weapons = node["weapons"].size();
    int textures = node["textures"].size();
    int decorations = node["decorations"].size();
    int walkables = node["walkable"].size();
    for (auto &vector:matrix) {
        for (auto &id:vector) {
            if (id < 0
                || (id > items && id < WEAPONS_START_AT)
                || (id >= weapons + WEAPONS_START_AT && id < TEXTURES_START_AT)
                || (id > textures + TEXTURES_START_AT && id < DECORATIONS_START_AT)
                || (id > decorations + DECORATIONS_START_AT && id < WALKABLE_START_AT)
                || id >= walkables + WALKABLE_START_AT) {
                return false;
            }
        }
    }
    return true;
}
