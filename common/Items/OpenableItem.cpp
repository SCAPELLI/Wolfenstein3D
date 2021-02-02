

#include "OpenableItem.h"

OpenableItem::OpenableItem(int id,std::string name, int effect)
:  id(id), name(name), effect(effect), Item(id, name, effect){}


bool OpenableItem::isConsumed(Player &player) {
    //poner que se abre, poner sleep y despues volver a cambiar el valor
    return false;
}