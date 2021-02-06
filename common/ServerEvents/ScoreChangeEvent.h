

#ifndef CAMERA_CPP_SCORECHANGEEVENT_H
#define CAMERA_CPP_SCORECHANGEEVENT_H
#include "../AbstractEvent.h"

class ScoreChangeEvent  : public AbstractEvent{
public:
    int score;
    ScoreChangeEvent(int score);
};


#endif //CAMERA_CPP_SCORECHANGEEVENT_H
