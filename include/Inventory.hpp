#pragma once
#include <iostream>
#include "Item.hpp"
#include "LinkedList.hpp"
#include "Character.hpp"
using namespace std;

class Inventory {
private:
    static Inventory* sInstance;
    LinkedList<Item*> items;

private:
    Inventory();
    ~Inventory();

public:
    static Inventory* instance();
    static void release();
    void insertItem(Item *item);
    void removeItem(Item *item);
    Item* searchItemByIndex(int index);
    void sort(); // Create this function Faiq!!
    void printItems();
    void printOptions();
    void printSubOptions();
    void input(Character* character);
    void inputSubOptions(Character* character, Item* item);
};