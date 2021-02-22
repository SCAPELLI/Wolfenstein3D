

#ifndef CAMERA_CPP_WALLRAY_H
#define CAMERA_CPP_WALLRAY_H
#include "Vector.h"
#include <vector>
#include "Map.h"

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
