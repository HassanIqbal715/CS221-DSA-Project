#include "include/Functions.hpp"

void printTitle() {
    cout << "         _____ _____            _   _  ____  _                _____\n";
    cout << "        / ____|  __ \\     /\\   | \\ | |/ __ \\| |        /\\    / ____|\n";       
    cout << "       | |  __| |__) |   /  \\  |  \\| | |  | | |       /  \\  | (___\n";         
    cout << "       | | |_ |  _  /   / /\\ \\ | . ` | |  | | |      / /\\ \\  \\___ \\\n";        
    cout << "       | |__| | | \\ \\  / ____ \\| |\\  | |__| | |____ / ____ \\ ____) |\n";      
    cout << "        \\_____|_|_ \\_\\/_/____\\_\\_| \\_|\\____/|______/_/____\\_\\_____/  _____\n";
    cout << "     /\\   |  __ \\ \\    / /  ____| \\ | |__   __| |  | |  __ \\|  ____|/ ____|\n";
    cout << "    /  \\  | |  | \\ \\  / /| |__  |  \\| |  | |  | |  | | |__) | |__  | (___\n";
    cout << "   / /\\ \\ | |  | |\\ \\/ / |  __| | . ` |  | |  | |  | |  _  /|  __|  \\___ \\\n"; 
    cout << "  / ____ \\| |__| | \\  /  | |____| |\\  |  | |  | |__| | | \\ \\| |____ ____) |\n";
    cout << " /_/    \\_\\_____/   \\/   |______|_| \\_|  |_|   \\____/|_|  \\_\\______|_____/\n"; 
    cout << '\n';                                                                           
}

void printUserBalance() {
    cout << "Balance: " << userBalance << " Rs\n";
}

void printHealthBar(int currentHealth, int maxHealth) {
    float percentage = float(float(currentHealth) / maxHealth) * 100;
    for (int i = 0; i < percentage; i += 5) {
        cout << "|";
    }
}

void fixStringCase(string& text) {
    if (text[0] >= 'a' && text[0] <= 'z') {
        text[0] -= 32;
    }

    for (int i = 1; i < text.size(); i++) {
        if (text[i - 1] != ' ') { 
            if (text[i] >= 'A' && text[i] <= 'Z') {
                text[i] += 32;
            }
        }
        else {
            if (text[i] >= 'a' && text[i] <= 'z') {
                text[i] -= 32;
            }
        }
    }
}

void cleanSaveFiles() {
    // removes everything by opening the file normally
    ofstream characterFile("database/saveCharacters.txt");
    characterFile.close();
    ofstream inventoryFile("database/saveInventory.txt");
    inventoryFile.close();
}

void saveCharacterData(Character *&character) {
    // opens the file in append mode
    ofstream saveFile("database/saveCharacters.txt", ios::app);

    if (saveFile.is_open()) {
        saveFile << character->getName() << "," 
                << character->getHealth() << "," 
                << character->getMaxHealth() << "," 
                << character->getBaseAttack() << "," 
                << character->getBaseDefense() << "," 
                << character->getBaseSpeed() << ","
                << character->getLevel() << ","
                << character->getExp() << ","
                << character->getTargetExp() << ",";

        saveFile << (character->getWeapon() ? character->getWeapon()->getName() : "None") << ",";

        for (int i = 0; i < 4; ++i) {
            saveFile << (character->getArmor()[i] ? character->getArmor()[i]->getName() : "None") << ",";
        }

        saveFile << "\n";
        saveFile.close();
    } 
    else {
        cout << "Failed to open the save file.\n";
    }
}

vector<Character*> loadCharacterData() {
    vector<Character*> characters;
    ifstream loadFile("database/saveCharacters.txt");

    if (!loadFile.is_open()) {
        cout << "Failed to open the save file.\n";
        return characters;
    }

    string line;
    while (getline(loadFile, line)) {
        stringstream ss(line);

        string name, weaponName, healthStr, maxHealthStr, baseAttackStr, baseDefenseStr, baseSpeedStr;
        string levelStr, expStr, targetExpStr;
        string armorNames[4];
        int health, maxHealth, baseAttack, baseDefense, baseSpeed, level, exp, targetExp;

        getline(ss, name, ',');
        getline(ss, healthStr, ',');
        getline(ss, maxHealthStr, ',');
        getline(ss, baseAttackStr, ',');
        getline(ss, baseDefenseStr, ',');
        getline(ss, baseSpeedStr, ',');
        getline(ss, levelStr, ',');
        getline(ss, expStr, ',');
        getline(ss, targetExpStr, ',');
        getline(ss, weaponName, ',');
        for (int i = 0; i < 4; ++i) {
            getline(ss, armorNames[i], ',');
        }

        // Convert string to integer values
        health = stoi(healthStr);
        maxHealth = stoi(maxHealthStr);
        baseAttack = stoi(baseAttackStr);
        baseDefense = stoi(baseDefenseStr);
        baseSpeed = stoi(baseSpeedStr);
        level = stoi(levelStr);
        exp = stoi(expStr);
        targetExp = stoi(targetExpStr);
        Character* character = new Character(name, health, baseAttack, baseDefense, baseSpeed, level, exp, targetExp);

        if (weaponName != "None") {
            Weapon* weapon = dynamic_cast<Weapon*>(Shop::instance()->getItemByName(weaponName)->clone());
            character->setWeapon(*weapon);
        }

        for (int i = 0; i < 4; ++i) {
            if (armorNames[i] != "None") {
                Armor* armor = dynamic_cast<Armor*>(Shop::instance()->getItemByName(armorNames[i])->clone());
                character->setArmor(*armor);
            }
        }

        characters.push_back(character);
    }

    loadFile.close();
    return characters;
}