#include <iostream>
#include "Enemy.hpp"
#include "Inventory.hpp"
#include "Shop.hpp"
#include "GlobalVariables.hpp"
#include "Functions.hpp"

using namespace std;

class Game {
private:
    static Game* sInstance;
    LinkedList<Enemy*> enemies;

private:
    Game();
    ~Game();

public:
    static Game* instance();

    void fight(Character *&character);
    void play(Character *&character);
    void printMenu();
    void input(Character *&character);
    void loadEnemiesFromFile();

    static void release();
};
