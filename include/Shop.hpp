#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "Item.hpp"
#include "LinkedList.hpp"
#include "Inventory.hpp"

using namespace std;
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
    void loadItemsFromFile();

    void removeItemByIndex(int index);
    Item* getItemByIndex(int index);
    Item* getItemByName(string name);

    void print();
    void printOptions();
    
    int input(Character *& character);
    void purchase(Item *item);
    void sell(Item *item);

    void releaseElements();
    static void release();
};