#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
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
    srand(time(0));
    initGlobalVar();
    int option{-1};
    int characterOption{-1};

    // Character* granola = new Character("Granola", 1000, 150, 150, 200);
    // Character* peanut = new Character("Peanut", 600, 400, 50, 250);
    // Character* abdullah = new Character("Fake Abdullah", 2500, 100, 200, 150);

    Character* granola = nullptr;
    Character* peanut = nullptr;
    Character* abdullah = nullptr;

    vector<Character*> characters = loadCharacterData();
    granola = characters[0];
    peanut = characters[1];
    abdullah = characters[2];
    Inventory::instance()->loadInventory();

    printTitle();
    
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

            case 0:
                gameRunner = false;
                break;

            default:
                cout << "Invalid input";
                continue;
        }
    }

    cleanSaveFiles();
    saveCharacterData(granola);
    saveCharacterData(peanut);
    saveCharacterData(abdullah);
    Inventory::instance()->saveInventory();

    Inventory::release();
    Menu::release();
    Shop::release();

    delete granola;
    delete peanut;
    delete abdullah;
    return 0;
}