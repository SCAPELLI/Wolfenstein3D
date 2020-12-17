
#ifndef WOLFENSTEIN3D_WEAPON_H
#define WOLFENSTEIN3D_WEAPON_H


class Weapon{
public:
    int id;
    int damage;
    int bullets;
    int minBullets;
    double speed;

public:
    int getDamage()const;
    Weapon(int id, int damage, int bullets, int minBullets, double speed);
    int attack();
    void addBullets(int moreBullets);
    int getSpeed();
    bool operator<(const Weapon& t) const;
    bool operator==(const Weapon& t) const;
};

#endif //WOLFENSTEIN3D_WEAPON_H
