
#include "Map.h"
#include <yaml-cpp/yaml.h>
#include "Game.h"


class GameLoader{

public:
    GameLoader();
    void configPlayer(int& lifes, int& health, int& radius, double& angle);
    void readData(std::vector<std::vector<int>>& map,
                                            std::vector<Player>& players);
    void mapLoader(std::vector<std::vector<int>>& map,
                   std::vector<Player>& players, YAML::Node& matrix);
    ~GameLoader();
};