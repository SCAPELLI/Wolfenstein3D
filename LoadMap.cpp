
#include <yaml-cpp/yaml.h>
#include <Player.h>
#include <vector>


void readYaml(){
    YAML::Node config = YAML::LoadFile("map.yaml");
    std::vector<int> map;
    YAML::Node matrix = config["map"];
    int player_id = config["info"]["player"]["id"].as<int>();
    int wall_id = config["info"]["Wall"]["id"].as<int>();
    int length = config["lenght"].as<int>();
    int width = config["with"].as<int>();

    for (std::size_t i = 0; i < matrix.size(); i++) {
        for (std::size_t j = 0; j < matrix[i].size(); j++) {
            int elem = matrix[i][j].as<int>();
            if (elem == player_id){
                Player player(player_id,i * width, j * length);
            } else if (elem == wall_id) {
                map.push_back(elem);
            } else {
                map.push_back(0);
            }
        }
   }
}


