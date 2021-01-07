#include "Item.h"
#include "../cliente/Sprite.h"

Item::Item(int id, Sprite &newSprite)
:    id(id), sprite(newSprite)
{}

int Item::getItemId(){
    return id;
}