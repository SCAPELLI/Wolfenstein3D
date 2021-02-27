#include "QuitEvent.h"
#include "../server/GameStage.h"
#include "../common/EventSerializer.h"

QuitEvent::QuitEvent() {}

void QuitEvent::runHandler(GameStage& gameStage) {
    gameStage.processEvent(*this);
}

bool QuitEvent::thisIsTheQuitEvent() {
    return true;
}
std::string QuitEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}
