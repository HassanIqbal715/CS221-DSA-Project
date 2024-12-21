#pragma once
#include <iostream>
#include "Item.hpp"
using namespace std;

class Character {
private:
    string name;
    int level;
    int exp;
    int targetExp;
    int health;
    int maxHealth;
    int attack;
    int baseAttack;
    int defense;
    int baseDefense;
    int speed;
    int baseSpeed;
    Weapon* weapon;
    Armor** armorSet;
    // add skills here

public:
    Character();
    Character(string name, int health, int attack, int defense, int speed);

    void setName(string name);
    void setExp(int exp);
    void setHealth(int health);
    void setAttack(int attack);
    void setDefense(int defense);
    void setSpeed(int speed);
    void setWeapon(Weapon &weapon);
    void setArmor(Armor &armor);
    string getName();
    int getLevel();
    int getExp();
    int getTargetExp();
    int getHealth();
    int getMaxHealth();
    int getAttack();
    int getDefense();
    int getSpeed();
    Weapon* getWeapon();
    Armor** getArmor();

    bool checkLevelUp();
    void levelUp();
    void consumeItem(Food &food);

    ~Character();
};