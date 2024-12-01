#pragma once
#include <iostream>
using namespace std;

class Item {
protected:
    string name;
    int price;
    int ID;
    static int itemCount;

public:
    Item();
    Item(Item &item);
    Item(string name, int price);
    void setName(string name);
    void setPrice(int price);
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
    Armor(Armor& armor);
    Armor(string name, int price, Type type, int defense);
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
    Food(Food& food);
    Food(string name, int price, int health);
    void setHealth(int health);
    int getHealth();
};

class Weapon : public Item {
public:
    enum Type {SWORD, AXE, POLEARM, STAFF, BOW, NONE};

private:
    Type type;
    int attack;
    int speed;

public:
    Weapon();
    Weapon(Weapon& weapon);
    Weapon(string name, int price, Type type, int attack, int speed);
    void setType(Type type);
    void setAttack(int attack);
    void setSpeed(int speed);
    Type getType();
    int getAttack();
    int getSpeed();
};