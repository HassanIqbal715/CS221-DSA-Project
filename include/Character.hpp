#include <iostream>
#include "Item.hpp"
using namespace std;

class Character {
private:
    string name;
    int level;
    int exp;
    int health;
    int attack;
    int defense;
    int speed;
    Weapon* weapon;
    Armor** armorSet;
    // add skills here

public:
    Character();
    Character(string name, int health, int attack, int defense, int speed);

    void setName(string name);
    void setExp();
    void setHealth(int health);
    void setAttack(int attack);
    void setDefense(int defense);
    void setSpeed(int speed);
    void setWeapon(Weapon weapon);
    void setArmor(Armor armor);
    string getName();
    int getLevel();
    int getExp();
    int getHealth();
    int getAttack();
    int getDefense();
    int getSpeed();
    Weapon* getWeapon();
    Armor** getArmor();

    ~Character();
};