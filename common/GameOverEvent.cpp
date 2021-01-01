
#include "GameOverEvent.h"
#include "../cliente/CGame.h"

GameOverEvent::GameOverEvent(GameOverEvent& gameOverEvent){}

GameOverEvent::GameOverEvent(int idPlayer) : idPlayer(idPlayer){}

void GameOverEvent::runHandler(CGame& game){

}
