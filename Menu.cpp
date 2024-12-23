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

void Menu::print() {
    cout << "Main Menu\n";
    cout << "\t1. Play\n";
    cout << "\t0. Exit\n";
}