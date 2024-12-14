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
    void sort(); // Create this function Faiq!!
    void printItems();
    void printOptions();
    void printSubOptions();
    void input(Character* character);
    void inputSubOptions(Character* character, Item* item);
};