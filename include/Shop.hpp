#pragma once
#include "Item.hpp"
#include "LinkedList.hpp"

class Shop {
private:
    static Shop* sInstance;
    LinkedList<Item*> items;

private:
    Shop();
    ~Shop();

public:
    static Shop* instance();

    void addArmor(string name, int price, Armor::Type type, int defense);
    void addFood(string name, int price, int health);
    void addWeapon(string name, int price, Weapon::Type type, int attack, int speed);
    
    void removeItemByIndex(int index);
    Item* getItemByIndex(int index);
    Item* getItemByName(string name);

    void print();
    void printOptions();

    void input();
    void purchase();

    void releaseElements();
    static void release();
};