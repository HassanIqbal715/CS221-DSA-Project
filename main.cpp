#include <iostream>
#include "include/Functions.hpp"
#include "include/Game.hpp"
#include "include/GlobalVariables.hpp"
#include "include/Inventory.hpp"
#include "include/Item.hpp"
#include "include/LinkedList.hpp"
#include "include/Menu.hpp"
#include "include/Shop.hpp"

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