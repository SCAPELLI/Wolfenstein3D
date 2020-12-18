
#include "Map.h"
#include <yaml-cpp/yaml.h>
#include "Game.h"


class GameLoader{

public:
    GameLoader();
    void configPlayer(int& lifes, int& health, int& radius,
                      double& angle, std::map<int, Weapon>& bag, int& idWeapon);
    void readData(std::vector<std::vector<int>>& map,
                  std::vector<Player>& players,  int& speed);
    void mapLoader(std::vector<std::vector<int>>& map,
                   std::vector<Player>& players, YAML::Node& matrix);
    ~GameLoader();
};