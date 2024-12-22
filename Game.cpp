#include "include/Game.hpp"

Game* Game::sInstance = nullptr;

Game::Game() {
    Inventory::instance();
    loadEnemiesFromFile();
}

Game::~Game() {
    release();
}

Game* Game::instance() {
    if (sInstance == nullptr)
        sInstance = new Game();
    return sInstance;
}

void Game::play(Character *&character) {
    int option = 0;
    while (gameRunner) {
        printMenu();
        cout << "Enter your option: " << '\n';
        switch(option) {
            case 1:
                fight(character);
                break;
        }
    }
}

void Game::fight(Character *&character) {
    int enemyIndex = rand() % enemies.getSize();
    int enemyLevel = character->getLevel() - rand() % character->getLevel() + (rand() % character->getLevel()) / 2;

    Enemy currentEnemy = *(enemies.searchNodeByIndex(enemyIndex)->data);
    currentEnemy.scaleStats(enemyLevel);

    cout << "A wild " << currentEnemy.getName() << " has appeared!.\n\n";
    bool isFighting = true;

    while (isFighting) {
        static int option;
        cout << "---------------------------\n";
        cout << currentEnemy.getName() << endl;
        cout << "LVL. " << enemyLevel << endl;
        printHealthBar(currentEnemy.getHealth(), currentEnemy.getMaxHealth());
        cout << currentEnemy.getHealth() << " / " << currentEnemy.getMaxHealth();

        cout << "\n\n";
        cout << character->getName() << endl;
        cout << "LVL. " << character->getLevel() << endl;
        cout << "EXP. " << character->getExp() << " / " << character->getTargetExp();
        cout << endl;
        printHealthBar(character->getHealth(), character->getMaxHealth());
        cout << character->getHealth() << " / " << character->getMaxHealth();

        cout << "\n\n";
        cout << "1. Attack\t";
        cout << "2. Open Inventory\n";
        cout << "3. Use Skill\t";
        cout << "0. Run\n";
        cout << "Enter your option: ";
        cin >> option;

        switch (option) {
            case 1:
                if (character->getSpeed() > currentEnemy.getSpeed()) {

                    cout << "You deal " << currentEnemy.takeDamage(character->getAttack()) << " damage!\n";

                    if (currentEnemy.checkDead()) {
                        cout << currentEnemy.getName() << " is dead! You won!\n";
                        Inventory::instance()->insertItem(currentEnemy.getDropItem());
                        userBalance += currentEnemy.getDropCoins();
                    
                        character->gainExp(currentEnemy.getDropCoins() * enemyLevel * 
                                           character->getLevel());

                        cout << "You gained " << currentEnemy.getDropCoins() << " coins!\n";

                        if (character->checkLevelUp()) {
                            character->levelUp();
                            character->printLevelUpMessage();
                        }

                        isFighting = false;
                        break;
                    }

                    cout << "You take " << character->takeDamage(currentEnemy.getAttack()) << " damage!\n";

                    if (character->checkDead()) {
                        userBalance -= currentEnemy.getDropCoins();
                        isFighting = false;
                        cout << "You lost " << currentEnemy.getDropCoins() << " Rs" << "\n";
                        cout << "You died...";
                        break;
                    }
                }
                else {
                    cout << "You take " << character->takeDamage(currentEnemy.getAttack()) << " damage!\n";
                    if (character->checkDead()) {
                        userBalance -= currentEnemy.getDropCoins();
                        isFighting = false;
                        cout << "You lost " << currentEnemy.getDropCoins() << " Rs" << "\n";
                        cout << "You died...";
                        break;
                    }

                    cout << "You deal " << currentEnemy.takeDamage(character->getAttack()) << " damage!\n";

                    if (currentEnemy.checkDead()) {
                        Inventory::instance()->insertItem(currentEnemy.getDropItem());
                        userBalance += currentEnemy.getDropCoins();
                    
                        character->gainExp(currentEnemy.getDropCoins() * enemyLevel * 
                                           character->getLevel());
                        
                        cout << "You gained " << currentEnemy.getDropCoins() << " coins!\n";

                        if (character->checkLevelUp()) {
                            character->levelUp();
                            character->printLevelUpMessage();
                        }

                        isFighting = false;
                        break;
                    }                    
                }
                break;
            
            case 2:
                Inventory::instance()->printItems();
                Inventory::instance()->printOptions();
                cout << "Enter your option: ";
                if (Inventory::instance()->input(character) == 0) {
                    cout << "You take " << character->takeDamage(currentEnemy.getAttack()) << " damage!\n";
                    if (character->checkDead()) {
                        userBalance -= currentEnemy.getDropCoins();
                        isFighting = false;
                        cout << "You lost " << currentEnemy.getDropCoins() << " Rs" << "\n";
                        cout << "You died... GAMEOVER... \n";
                        break;
                    }
                }

                break;
            
            case 3:
                // Add skills stuff here
                break;

            case 0:
                if (rand()%10 + 1 > 4) {
                    cout << "You managed to run away!\n";
                    isFighting = false;
                }
                else {
                    cout << "You could not run away...\n";                    
                    cout << "You take " << character->takeDamage(currentEnemy.getAttack()) << " damage!\n";
                    if (character->checkDead()) {
                        userBalance -= currentEnemy.getDropCoins();
                        isFighting = false;
                        cout << "You lost " << currentEnemy.getDropCoins() << " Rs" << "\n";
                        cout << "You died... GAMEOVER... \n";
                        break;
                    }
                }
                break;

            default:
                cout << "Invalid input.\n";
                break;
        }
    }   
}

void Game::printMenu() {
    cout << "Main Menu\n";
    cout << "\t1. Fight Enemies!\n";
    cout << "\t2. Inventory\n";
    cout << "\t3. Skills\n";
    cout << "\t4. Shop\n";
    cout << "\t5. Check Equipment\n";
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
                fight(character);
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
                while (option != 0) {
                    cout << "\n---------------------------\n";
                    Shop::instance()->print();
                    cout << "\n---------------------------\n";
                    Shop::instance()->printOptions();
                    cout << "Enter your option: ";
                    option = Shop::instance()->input(character);
                }
                option = -1;
                break;
            
            case 5:
                character->printEquipment();
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

void Game::loadEnemiesFromFile() {
    ifstream file("database/enemies.txt");
    string line;

    if (!file.is_open()) {
        cout << "Failed to open enemies.txt\n";
        return;
    }

    while (getline(file, line)) {
        istringstream stream(line);
        string name, itemDropName;
        int health, attack, speed, defense, level, coinsDrop;

        getline(stream, name, ',');
        stream >> health; stream.ignore();
        stream >> attack; stream.ignore();
        stream >> speed; stream.ignore();
        stream >> defense; stream.ignore();
        getline(stream, itemDropName, ',');
        stream >> coinsDrop;

        Item* dropItem = Shop::instance()->getItemByName(itemDropName);

        if (dropItem == nullptr) {
            cout << "Error: Item " << itemDropName << " not found\n";
            continue;
        }

        Enemy* enemy = new Enemy(name, health, attack, speed, defense, dropItem, coinsDrop);
        enemies.push_back(enemy);
    }
    file.close();
}

void Game::release() {
    if (sInstance == nullptr)
        return;

    delete sInstance;
    sInstance = nullptr;
}