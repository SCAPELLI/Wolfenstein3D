
#include "server/include/WallRay.h"
#include <cmath>
#include "server/include/Map.h"
WallRay::WallRay(Vector position, double degrees):
        startPoint(position),
        direction(cos(position.x), sin(position.y)),
        deltaDistX(std::abs(1 / direction.x)),
        deltaDistY(std::abs(1 / direction.y))

{
    this->initialize(startPoint);
}

void WallRay::initialize(Vector& position){
    int mapX = position.scale().y;
    int mapY = position.scale().x;
    double posX = position.y / 32;
    double posY = position.x / 32;
    if (direction.x < 0){
        this->stepX = -1;
        this->sideDistX = (posX - mapX) * deltaDistX;
    } else {
        this->stepX = 1;
        this->sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (direction.y < 0){
        this->stepY = -1;
        this->sideDistY = (posY - mapY) * deltaDistY;
    } else {
        this->stepY = 1;
        this->sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }
}

double WallRay::distanceToWall(Map& map){
    int mapX = startPoint.scale().y;
    int mapY = startPoint.scale().x;
    double posX = startPoint.y / 32;
    double posY = startPoint.x / 32;
    while (true){
        if (sideDistX < sideDistY){
            sideDistX += deltaDistX;
            mapX += stepX;

        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
        }
        Vector pos = Vector((int)mapY, (int)mapX);
        if (!map.isOkToMove(pos)){
            return pow(pow(mapY * 32, 2) + pow(mapX * 32, 2), 0.5);
        }
    }
}


WallRay::~WallRay() {}