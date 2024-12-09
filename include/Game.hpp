#include <iostream>
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

    static void release();
};
