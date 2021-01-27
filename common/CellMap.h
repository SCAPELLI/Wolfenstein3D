#ifndef CELLMAP_H
#define CELLMAP_H

#include <vector>

class Item;
class Player;

class CellMap{
    bool occupied;
    std::vector<Item> items;
    std::vector<Player> playerList;
public:
    CellMap();
    //void transferPlayer(CellMap& otherCell);
    void removePlayer(Player& player);
    void addPlayer(Player& entity);
    bool hasPlayer();
    bool isSolid();
    void getItemsTile(Player& player);
    bool hasItems();
    Item removeItem();
    void addItem(Item item);
    void setSolid();
    void dropItems(Player& player);
    void dropItemPlayer(Item item);

};


#endif //CELLMAP_H
