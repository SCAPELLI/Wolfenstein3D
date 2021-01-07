#ifndef CELLMAP_H
#define CELLMAP_H

#include <vector>

class Item;
class Player;

class CellMap{
    bool occupied;
    Player* player;
    std::vector<Item*> items;
public:
    CellMap();
    void transferPlayer(CellMap& otherCell);
    void removePlayer();
    void addPlayer(Player* entity);
    bool hasPlayer();
    bool isSolid();
    Player* getPlayer();
    int getItemId();
    bool hasItems();
    Item* removeItem();
    void addItem(Item* item);
    void setSolid();

};


#endif //CELLMAP_H
