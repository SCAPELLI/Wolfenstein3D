#include "common/include/QuitEvent.h"
#include "server/include/GameStage.h"
#include "common/include/EventSerializer.h"

QuitEvent::QuitEvent(int playerId): playerId(playerId) {}

void QuitEvent::runHandler(GameStage& gameStage) {
    gameStage.processEvent(*this);
}

bool QuitEvent::thisIsTheQuitEvent() {
    return true;
}
std::string QuitEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}
