#include "MovementEvent.h"
#include "GameStage.h"

void MovementEvent::runHandler(GameStage& gameStage) {
    gameStage.processEvent(*this);
}
