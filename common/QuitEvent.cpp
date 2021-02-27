#include "QuitEvent.h"
#include "../server/GameStage.h"

QuitEvent::QuitEvent() {}

void QuitEvent::runHandler(GameStage& gameStage) {}

bool QuitEvent::thisIsTheQuitEvent() {
    return true;
}
