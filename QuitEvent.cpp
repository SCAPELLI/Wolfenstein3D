#include "QuitEvent.h"
#include "GameStage.h"

void QuitEvent::runHandler(GameStage& gameStage) {}

bool QuitEvent::thisIsTheQuitEvent() {
    return true;
}
