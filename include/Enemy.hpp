#pragma once
#include <iostream>
#include "Item.hpp"
using namespace std;

class Enemy {
private:
    string name;
    int health;
    int maxHealth;
    int attack;
    int baseAttack;
    int defense;
    int baseDefense;
    int speed;
    int baseSpeed;
    Item* drop;
    int coins;

public:
    Enemy();
    Enemy(string name, int health, int attack, int speed, int defense, Item* drop, int coins);

    void setName(string name);
    void setHealth(int health);
    void setAttack(int attack);
    void setDefense(int defense);
    void setSpeed(int speed);
    void setDropItem(Item* drop);
    void setDropCoins(int coins);

    string getName();
    int getHealth();
    int getMaxHealth();
    int getAttack();
    int getDefense();
    int getSpeed();
    Item* getDropItem();
    int getDropCoins();

    void scaleStats(int level);
    int takeDamage(int damage);
    bool checkDead();

    ~Enemy();
};