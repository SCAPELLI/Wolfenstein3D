#include "Player.h"
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include "MapLoader.h"

int main(){
    MapLoader map2;
    map2.readYaml();
    return 0;
}
