#pragma once
#include <iostream>
using namespace std;

class Item {
protected:
    string name;
    int price;
    int ID;

public:
    Item();
    Item(string name, int price, int ID);
    void setName(string name);
    void setPrice(int price);
    void setID(int ID);
    string getName();
    int getPrice();
    int getID();
};

class Armor : public Item {
public:
    enum Type {HELMET, CHESTPLATE, LEGGINGS, BOOTS};

private:
    Type type;
    int defense;

public:
    Armor();
    Armor(string name, int price, int ID, Type type, int defense);
    void setType(Type type);
    void setDefense(int defense);
    Type getType();
    int getDefense();
};

class Food : public Item {
private:
    int health;

public:
    Food();
    Food(string name, int price, int ID, int health);
    void setHealth(int health);
    int getHealth();
};

class Weapon : public Item {
public:
    enum Type {SWORD, AXE, POLEARM, STAFF, BOW};

private:
    Type type;
    int attack;
    int speed;

public:
    Weapon();
    Weapon(string name, int price, int ID, Type type, int attack, int speed);
    void setType(Type type);
    void setAttack(int attack);
    void setSpeed(int speed);
    Type getType();
    int getAttack();
    int getSpeed();
};