#include "Renderer.h"

void processEvent(LifeDecrementEvent& event) {
    std::cout<<"Se llamo al procesador del evento LifeDecrement"<<std::endl;

}
void processEvent(ShootingEvent& event) {
    std::cout<<"Se llamo al procesador del evento Shooting"<<std::endl;
}

void processEvent(PositionEvent& event) {
    std::cout<<"Se llamo al procesador del evento Position"<<std::endl;
}
