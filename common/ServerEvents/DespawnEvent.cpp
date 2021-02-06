
#include "DespawnEvent.h"

DespawnEvent::DespawnEvent(int id, int type) : id(id), type(type) {}

void DespawnEvent::runHandler(GameStage &gameStage) {}