
#include "GameOverEvent.h"
#include "../cliente/CGame.h"
#include "EventSerializer.h"

//GameOverEvent::GameOverEvent(GameOverEvent& gameOverEvent){}

GameOverEvent::GameOverEvent(int idPlayer) : idPlayer(idPlayer){}

void GameOverEvent::runHandler(CGame& game){

}

std::string GameOverEvent::getSerialization() {
    return EventSerializer::serialize(*this);
}
