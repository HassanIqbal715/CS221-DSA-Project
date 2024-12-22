#pragma once
#include <iostream>
#include <string>
#include "Item.hpp"
#include "Functions.hpp"
#include "LinkedList.hpp"
#include "Character.hpp"
#include <typeinfo>
using namespace std;

class Inventory {
private:
    static Inventory* sInstance;
    LinkedList<Item*> items;

    LinkedList<Item*>::Node* split(LinkedList<Item*>::Node* /*head*/);

    LinkedList<Item*>::Node* mergeSort(LinkedList<Item*>::Node* /*head*/);

    LinkedList<Item*>::Node* merge(LinkedList<Item*>::Node* /*list1*/, 
        LinkedList<Item*>::Node* /*list2*/);
private:
    Inventory();
    ~Inventory();

public:
    static Inventory* instance();
    static void release();

    void insertItem(Item *item);
    void removeItem(Item *item);

    Item* searchItemByIndex(int index);
    Item* searchItemByName(string name);

    void sort();

    void printItems();
    void printOptions();
    void printSubOptions();

    void saveInventory();
    int input(Character* character);
    void inputSubOptions(Character* character, Item* item);
};