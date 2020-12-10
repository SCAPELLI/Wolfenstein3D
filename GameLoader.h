
#include "Map.h"
#include <yaml-cpp/yaml.h>
#include "Game.h"


class GameLoader{

public:
    GameLoader();
    Game readData();
    void mapLoader(std::vector<std::vector<int>>& map, Player& player,
                                                         YAML::Node& matrix);
};