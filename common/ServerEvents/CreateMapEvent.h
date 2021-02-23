

#ifndef CREATEMAPEVENT_H
#define CREATEMAPEVENT_H

#include "client/CGame.h"
#include "../Constants.h"
#include "../AbstractEvent.h"
#include "../../server/Vector.h"
#include <vector>
class CreateMapEvent   : public AbstractEvent{

public:
    updateEventType eventType;
    int width;
    int height;
    std::map<int, std::pair<int, int>> startingLocations;
    CreateMapEvent (updateEventType eventType, int width, int height);
    void addPlayer(int idPlayer, Vector& startingLocation);
    void runHandler(CGame& renderer) override;
    updateEventType getEventType() override;
};


#endif //CREATEMAPEVENT_H
