#pragma once
#include "item.hpp"
#include "LinkedList.hpp"

class Shop {
private:
    static Shop* sInstance;
    LinkedList<Item> items;

private:
    Shop();
    ~Shop();

public:
    static Shop* instance();
    void addItem();
    void removeItem();
    Item* getItemByIndex(int index);
    Item* getItemByName(string name);
    static void release();
};