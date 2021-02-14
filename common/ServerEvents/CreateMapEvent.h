

#ifndef CREATEMAPEVENT_H
#define CREATEMAPEVENT_H

#include "../cliente/CGame.h"

class CreateMapEvent   : public AbstractEvent{

public:
    int width;
    int height;
    CreateMapEvent (int width, int height);
    void runHandler(CGame& renderer) override;
};


#endif //CREATEMAPEVENT_H
