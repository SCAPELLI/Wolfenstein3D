#include "QuitEvent.h"
#include "../server/GameStage.h"

void QuitEvent::runHandler(GameStage& gameStage) {}

bool QuitEvent::thisIsTheQuitEvent() {
    return true;
}
