

#include "SpawnEvent.h"
#include "GameStage.h"

void SpawnEvent::runHandler(GameStage& gameStage) {
    //gameStage.processEvent(*this);
}

SpawnEvent::SpawnEvent(int id, int type, int posX, int posY)
: id(id), type(type), posX(posX), posY(posY) {}