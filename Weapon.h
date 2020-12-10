
#ifndef WOLFENSTEIN3D_WEAPON_H
#define WOLFENSTEIN3D_WEAPON_H


class Weapon{
    int id;
    int damage;
public:
    Weapon(int id, int damage);
    void attack();
    Weapon(Weapon&& other);

};

#endif //WOLFENSTEIN3D_WEAPON_H
