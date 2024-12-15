#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include "include/Functions.hpp"
#include "include/Game.hpp"
#include "include/GlobalVariables.hpp"
#include "include/Inventory.hpp"
#include "include/Item.hpp"
#include "include/LinkedList.hpp"
#include "include/Menu.hpp"
#include "include/Shop.hpp"
#include "include/Character.hpp"
using namespace std;

//  cout << "\n---------------------------\n"; use this to divide lines

int main() {
    initGlobalVar();
    printTitle();
    int option{-1};
    int characterOption{-1};

    Character* granola = new Character();
    Character* peanut = new Character();
    Character* abdullah = new Character();
    while (gameRunner) {
        cout << "\n---------------------------\n";
        Menu::instance()->print();
        cout << "Enter your option: ";
        cin >> option;
        // system("cls"); Commented out due to not working on linux
        // can use clear on linux machine but in turn will not work on windows
        switch (option) {
            case 1:
                cout << "\n---------------------------\n";
                cout << "Pick your character: " << endl;
                cout << "1. Granola" << endl;
                cout << "2. Peanut" << endl;
                cout << "3. Fake Abdullah" << endl;
                cout << "Enter your option: ";
                cin >> characterOption;

                if (characterOption < 1 || characterOption > 3)
                    cout << "Wrong input, but I assume you are here to play granola.\n";

                if (characterOption == 1)
                    Game::instance()->input(granola);
                else if (characterOption == 2)
                    Game::instance()->input(peanut);
                else if (characterOption == 3)
                    Game::instance()->input(abdullah);
                else {
                    Game::instance()->input(granola);
                }

                break;
            
            case 2:
                cout << "\n---------------------------\n";
                Shop::instance()->print();
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
    Inventory::release();
    Menu::release();
    Shop::release();
    return 0;
}