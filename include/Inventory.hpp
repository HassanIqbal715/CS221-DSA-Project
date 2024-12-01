#pragma once
#include <iostream>
#include "Item.hpp"
#include "LinkedList.hpp"
using namespace std;

class Inventory {
private:
    LinkedList<Item*> items;

public:
    Inventory();
    void insertItem(Item item);
    Item* searchItemByIndex(int index);
    void sort(); // Create this function Faiq!!
    void print();
};