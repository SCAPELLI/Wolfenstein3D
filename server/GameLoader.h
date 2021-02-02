#include <yaml-cpp/yaml.h>
#include "Game.h"
#include "../common/Item.h"


class GameLoader{
public:
    GameLoader();
    void configPlayer(int& lifes, int& health, int& radius,
                      double& angle, std::map<int, Weapon>& bag, int& idWeapon,
                      PointGainItem& points, KeyItem& keys, AmmoItem& bullets, bool dead);
    void readData(int& speed);
    Item* itemLoader(int& idItem);
    void configWeapon(std::string& name, int& effect, int& minBullets, double& speed);
    void setTexture(int& idItem, CellMap& tileMap);
    Item* itemLoader(std::string& idItem);
    void configItem(int& id, std::string&  itemName, int& effect);
    //    void mapLoader(std::vector<std::vector<int>>& map,
//                   std::vector<Player>& players, YAML::Node& matrix);
    ~GameLoader();
};