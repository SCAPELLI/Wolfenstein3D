#include "KeyItem.h"
#include "GameLoader.h"

KeyItem::KeyItem(int id,std::string name, int effect)
        :  id(id), name(name), effect(effect){}

KeyItem::KeyItem(){
    GameLoader yaml;
    name = "key";
    yaml.configItem(id, name, effect);
}
