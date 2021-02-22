#ifndef WOLFENSTEIN3D_PLAYER_H
#define WOLFENSTEIN3D_PLAYER_H
#include "Vector.h"
#include "Items/Weapon.h"
#include <map>
#include "Item.h"
#include <vector>
#include "Items/LifeGainItem.h"
#include "Items/AmmoItem.h"
#include "Items/PointGainItem.h"
#include "Items/KeyItem.h"
//#include "Items/Rocket.h"

class Player {
    std::string name;
    int id, relativeId;
    Vector position;
    Vector initialPosition;
    Vector scaledPosition;
    bool dead;
    int maxBullets, lifes;
    int health;
    int radius;
    double angle;
    std::map<int, Weapon> bag;
    int idWeapon;
    int bullets;
    int score;
    int keys;
    int bulletsShot;
    int playersKilled;
    int prevIdWeapon;
public:
    /*setea constructor del jugador*/
    Player(int parsed_id,int relativeId, std::string name, Vector position);

    /*Jugador es dañado y baja su vida devolviendo si murió o no*/
    int getDamage(int damage);

    /*Devuelve daño causado y actualiza valores de balas cuando daña otro jugador*/
    int hits(Player& otherPlayer);  //cambiar nombre funcion

    /* Devuelve distancia con otro jugador*/
    int distanceWith(Player& otherPlayer);

    /* Si se encuentra el arma pasada cambia esa a su actual */
    bool changeWeaponTo(int idToChange);

    /* Devuelve el ángulo del jugador*/
    double getAngle() const;

    /* Mueve el jugador a la posición indicada*/
    void move(Vector& newPos);

    /*rota cierta cantidad de grados*/
    void rotate(double newAngle);

    /*Devuelve el daño del arma actual*/
    int damageCurrentWeapon();

    /*Obtiene la posición del jugador*/
    Vector& getPosition();

    /* Obtiene la posición escalada del jugador*/
    Vector& getScaledPosition();

    /* Sobrecarga del operador == */
    bool operator==(const Player& player) const;

    /*Devuelve si el jugador colisionó con otro jugador */
    bool collideWith(int distance, int radius);
    bool pickupWeapon(Weapon weapon, std::vector<AbstractEvent*>& newEvents);
    void resetBagWeapons();
    int getBullets();
    void respawn();
    bool isDead();
    bool isGameOver();
    bool getItem(AmmoItem* item, std::vector<AbstractEvent*>& newEvents);
    bool getItem(LifeGainItem* item, std::vector<AbstractEvent*>& newEvents);
    bool getItem(PointGainItem* item, std::vector<AbstractEvent*>& newEvents);
    bool getItem(KeyItem* item, std::vector<AbstractEvent*>& newEvents);
    bool getItem(Weapon* item, std::vector<AbstractEvent*>& newEvents);
    bool openDoor();
    Weapon getWeapon();
    void setPosition(Vector initial);
    bool hasKey();
    void incrementCooldown();
    void initializePlayer(bool dead);
    int getId() const;
    int getLifes()const;
    bool doesHit(Player& otherPlayer);
    bool canShoot();
    bool shoot();
    double angleWithOther(Player& otherPlayer);
    void updateKills();
    bool hasRocketLauncher();
    Rocket* setRocket();
    Vector getInitialPosition();
    ~Player();

};

#endif //WOLFENSTEIN3D_PLAYER_H
