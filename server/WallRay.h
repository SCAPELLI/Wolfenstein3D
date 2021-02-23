

#ifndef CAMERA_CPP_WALLRAY_H
#define CAMERA_CPP_WALLRAY_H
#include "Vector.h"
#include <vector>
#include "Map.h"
/* Lanza rayos para calcular la distancia del jugador a la pared a donde está mirando */
class WallRay {
    Vector startPoint;
    Vector direction;
    double deltaDistX, deltaDistY, sideDistX, sideDistY;
    int stepX, stepY;
    void initialize(Vector& position);
public:
    double distanceToWall(Map& map);
    WallRay(Vector position, double degrees);
    ~WallRay();

};


#endif //CAMERA_CPP_WALLRAY_H
