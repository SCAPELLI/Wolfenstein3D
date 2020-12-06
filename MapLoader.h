#include <vector>
#include "Vector.h"



class MapLoader{

public:
    MapLoader();
    void readYaml();
    Vector generateRandom(int width, int lenght);
};