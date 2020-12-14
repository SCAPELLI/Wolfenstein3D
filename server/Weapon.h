
#ifndef WOLFENSTEIN3D_WEAPON_H
#define WOLFENSTEIN3D_WEAPON_H


class Weapon{
    int id;
    int damage;
    int bullets;
    int minBullets;
    int speed;

public:
    Weapon(int id, int damage, int bullets, int minBullets, int speed);
    int attack();
    Weapon(Weapon&& other);
    void addBullets(int moreBullets);
    int getSpeed();
};

#endif //WOLFENSTEIN3D_WEAPON_H
