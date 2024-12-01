#pragma once
#include <iostream>
#include "Item.hpp"
using namespace std;

class Inventory {
private:
    LinkedList<Item*> items;

public:
    void insertItem();
    Item* findItem(int ID);
    void sort(); // Create this function Faiq!!
    void print();
};