#include <iostream>
#include "include/functions.hpp"
#include "include/game.hpp"
#include "include/globalVariables.hpp"
#include "include/inventory.hpp"
#include "include/item.hpp"
#include "include/LinkedList.hpp"
#include "include/menu.hpp"
#include "include/shop.hpp"

using namespace std;

int main() {
    initGlobalVar();
    printTitle();
    int option{-1};

    while (gameRunner) {
        Menu::instance()->printMainMenu();
        cin >> option;
        switch (option) {
            case 1:
                break;
            case 2:
                Menu::instance()->printShop();
                break;
            case 3:
                break;
            case 0:
                gameRunner = false;
                break;
            default:
                cout << "Invalid input";
                continue;
        }
    }
    
    Menu::release();
    return 0;
}