#include <iostream>
#include "Inventory.hpp"
#include "Shop.hpp"
#include "GlobalVariables.hpp"

using namespace std;

class Game {
private:
    static Game* sInstance;

private:
    Game();
    ~Game();

public:
    static Game* instance();

    void fight();
    void play();
    void printMenu();
    void input(Character *&character);

    static void release();
};
