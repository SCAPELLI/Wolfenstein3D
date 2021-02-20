

#ifndef CREATEMAPEVENT_H
#define CREATEMAPEVENT_H

#include "../cliente/CGame.h"
#include "Constants.h"
#include "AbstractEvent.h"
#include "Vector.h"
#include <vector>
class CreateMapEvent   : public AbstractEvent{

public:
    updateEventType eventType;
    int width;
    int height;
    std::vector<Vector> startingLocations;
    CreateMapEvent (updateEventType eventType, int width, int height);
    void addPlayer(Vector startingLocation);
    void runHandler(CGame& renderer) override;
    updateEventType getEventType() override;
};


#endif //CREATEMAPEVENT_H
