#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>

class KillEvent;
class ShootingEvent;
class PositionEvent;

class Renderer {
public:
    void processEvent(KillEvent& event) {
        std::cout<<"Se llamo al procesador del evento KillEvent"<<std::endl;
    }
    void processEvent(ShootingEvent& event) {
        std::cout<<"Se llamo al procesador del evento Shooting"<<std::endl;
    }
    void processEvent(PositionEvent& event) {
        std::cout<<"Se llamo al procesador del evento Position"<<std::endl;
    }
};
#endif
