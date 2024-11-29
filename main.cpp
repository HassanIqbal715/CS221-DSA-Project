#include <iostream>
#include "include/functions.hpp"
#include "include/menu.hpp"
#include "include/globalVariables.hpp"
using namespace std;

int main() {
    initGlobalVar();
    printTitle();
    int option;
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