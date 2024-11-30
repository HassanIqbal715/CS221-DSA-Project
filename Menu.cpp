#include "include/Menu.hpp"

Menu* Menu::sInstance = nullptr;

Menu::Menu() {
    option = 0;
}

Menu::~Menu() {

}

// used initialize to access sInstance globally
Menu* Menu::instance() {
    // checks if sInstance is NULL and allocates memory to it if true.
    if (sInstance == nullptr) {
        sInstance = new Menu();
    }

    return sInstance;
}

// static function which deallocates memory
void Menu::release() {
    delete sInstance;
    sInstance = nullptr;
}

void Menu::printMainMenu() {
    cout << "Main Menu\n";
    cout << "\t1. Play\n";
    cout << "\t2. Shop\n";
    cout << "\t3. Skills\n";
    cout << "\t0. Exit\n";
}

void Menu::printShop() {
    cout << "Welcome to the shop!\n";
    cout << "_____________________________\n";
    cout << "   Items\tPrice\n";
    cout << "_____________________________\n";
    cout << "1. Potion\t100\n";
    cout << "2. Paralyze Heal\t150\n";
    cout << "3. Grimoire\t20000\n";
}
