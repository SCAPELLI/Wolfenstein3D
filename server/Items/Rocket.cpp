

#include "Rocket.h"
#include "../../common/ServerEvents/SpawnEvent.h"

Rocket::Rocket(int id, std::string name, int effect, int uniqueId) :
damage(0), impactPoint(Vector(0, 0 )),
sender(), currentPosition(currentPosition),
direction(direction), Item(id, name, effect, uniqueId){}



void Rocket::incrementCooldown(std::vector<AbstractEvent*>& newEvents){
    currentPosition.x += direction.x;
    currentPosition.y += direction.y;
    newEvents.push_back(new SpawnEvent(SpawnEventType, uniqueId,
                                       id, currentPosition.y,
                                       currentPosition.x ));
}

Vector Rocket::getPositionScaled(){
    return currentPosition.scale();
}