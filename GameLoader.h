
#include "Map.h"
#include <yaml-cpp/yaml.h>
#include "Game.h"


class GameLoader{

public:
    GameLoader();
    void readData(std::vector<std::vector<int>>& map, std::vector<Player>& players);
    void mapLoader(std::vector<std::vector<int>>& map, std::vector<Player>& players,
                                                         YAML::Node& matrix);
    ~GameLoader();
};