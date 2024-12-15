#include "include/Game.hpp"

Game* Game::sInstance = nullptr;

Game::Game() {

}

Game::~Game() {
    release();
}

Game* Game::instance() {
    if (sInstance == nullptr)
        sInstance = new Game();
    return sInstance;
}

void Game::play() {
    int option = 0;
    while (gameRunner) {
        printMenu();
        cout << "Enter your option: " << '\n';
        switch(option) {
            case 1:
                fight();
                break;
        }
    }
}

void Game::fight() {
    
}

void Game::printMenu() {
    cout << "Main Menu\n";
    cout << "\t1. Fight Enemies!\n";
    cout << "\t2. Inventory\n";
    cout << "\t3. Skills\n";
    cout << "\t4. Shop\n";
    cout << "\t0. Return to Title Screen\n";
}

void Game::input(Character *&character) {
    int option = -1;
    while (option != 0) {
        cout << "\n---------------------------\n";
        Game::instance()->printMenu();
        cout << "Enter your option: ";
        cin >> option;
    
        switch (option) {
            case 1:
                fight();
                break;

            case 2:
                while (option != 0) {
                cout << "\n------------------------------\n";
                Inventory::instance()->printItems();
                cout << "\n------------------------------\n";
                Inventory::instance()->printOptions();
                cout << "Enter your option: ";
                option = Inventory::instance()->input(character);
                }
                option = -1;
                break;

            case 3:
                break;

            case 4:
                cout << "\n---------------------------\n";
                Shop::instance()->print();
                break;

            case 0:
                option = 0;
                break;

            default:
                cout << "Invalid input.\n";
                break;
        }
    }
}

void Game::release() {
    if (sInstance == nullptr)
        return;

    delete sInstance;
    sInstance = nullptr;
}