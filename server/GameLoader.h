#include <yaml-cpp/yaml.h>
#include "Game.h"
#include "../common/Item.h"


class GameLoader{

public:
    GameLoader();
    void configPlayer(int& lifes, int& health, int& radius,
                      double& angle, std::map<int, Weapon>& bag, int& idWeapon,
                      Item& bullets);
    void readData(int& speed);
//    void mapLoader(std::vector<std::vector<int>>& map,
//                   std::vector<Player>& players, YAML::Node& matrix);
    ~GameLoader();
};