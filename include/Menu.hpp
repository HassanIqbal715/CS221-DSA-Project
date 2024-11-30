#pragma once
#include <iostream>
using namespace std;

// statically handled class to encapsulate main-menu related members in one class
class Menu {
private:
    /* private constructor and desctructor so the class can only be accessed through
    sInstance pointer */
    Menu();
    ~Menu();

private:
    static Menu* sInstance; // static instance which is used to access non-static members
    int option;

public:
    static Menu* instance();
    static void release();
    void printMainMenu();
    void printShop();
};