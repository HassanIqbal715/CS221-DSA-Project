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
    cout << "\t9. Return to Title Screen\n";
    cout << "\t0. Exit\n";
}

void Game::release() {
    if (sInstance == nullptr)
        return;

    delete sInstance;
    sInstance = nullptr;
}