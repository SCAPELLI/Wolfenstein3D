

#include "MapEvent.h"
#include "ServerEvents/SpawnEvent.h"
#include "ServerEvents/DespawnEvent.h"

MapEvent::MapEvent() {}

//void MapEvent::addItem(Item* item, int x, int y){
//    AbstractEvent* event = new SpawnEvent(item->getUniqueId(), item->getId(), x, y);
//    listEvents.insert(event);
//}
//void MapEvent::removeItem(Item* item){
//    AbstractEvent* event = new DespawnEvent(item->getUniqueId(), item->getId());
//    listEvents.insert(event);
//}