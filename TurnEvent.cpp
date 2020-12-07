#include "TurnEvent.h"
#include "GameStage.h"

void TurnEvent::runHandler(GameStage& gameStage) {
    gameStage.processEvent(*this);
}
