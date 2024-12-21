#include "include/Shop.hpp"

Shop* Shop::sInstance = nullptr;

Shop::Shop() {
    loadItemsFromFile();
}

Shop::~Shop() {

}

Shop* Shop::instance() {
    if (sInstance == nullptr)
        sInstance = new Shop();
    return sInstance;
}

void Shop::addArmor(string name, int price, Armor::Type type, int defense) {
    items.push_back(new Armor(name, price, type, defense));
}

void Shop::addFood(string name, int price, int health) {
    items.push_back(new Food(name, price, health));
}

void Shop::addWeapon(string name, int price, Weapon::Type type, int attack, int speed) {
    items.push_back(new Weapon(name, price, type, attack, speed));
}

void Shop::loadItemsFromFile() {
    ifstream file("database/items.txt");
    string line;

    while (std::getline(file, line)) {
        stringstream ss(line);
        string type;
        ss >> type;

        if (type == "Armor") {
            string name;
            int price, defense;
            string armorType;
            ss >> name >> price >> armorType >> defense;

            Armor::Type typeEnum;
            if (armorType == "HELMET") {
                typeEnum = Armor::HELMET;
            } else if (armorType == "CHESTPLATE") {
                typeEnum = Armor::CHESTPLATE;
            } else if (armorType == "LEGGINGS") {
                typeEnum = Armor::LEGGINGS;
            } else if (armorType == "BOOTS") {
                typeEnum = Armor::BOOTS;
            }

            addArmor(name, price, typeEnum, defense);
        }
        else if (type == "Food") {
            std::string name;
            int price, health;
            ss >> name >> price >> health;

            addFood(name, price, health);
        }
        else if (type == "Weapon") {
            string name;
            int price, attack, speed;
            string weaponType;
            ss >> name >> price >> weaponType >> attack >> speed;

            Weapon::Type typeEnum;
            if (weaponType == "SWORD") {
                typeEnum = Weapon::SWORD;
            } else if (weaponType == "AXE") {
                typeEnum = Weapon::AXE;
            } else if (weaponType == "STAFF") {
                typeEnum = Weapon::STAFF;
            } else if (weaponType == "BOW") {
                typeEnum = Weapon::BOW;
            }

            addWeapon(name, price, typeEnum, attack, speed);
        }
    }
}

void Shop::removeItemByIndex(int index) {
    items.deleteNodeByIndex(index);
}

Item* Shop::getItemByIndex(int index) {
    return items.searchNodeByIndex(index)->data;
}

Item* Shop::getItemByName(string name) {
    items.startIterator();
    
    for (int i = 0; i <= items.getSize(); i++) {
        if (items.getIterator()->data->getName().compare(name) == 0) {
            Item* tempItem = items.getIterator()->data;
            items.resetIterator();
            return tempItem;
        }     
        items.iterateOnce();
    }

    items.resetIterator();
    return nullptr;
}

void Shop::print() {
    items.startIterator();
    cout << "===========================================\n";
    cout << "        Welcome to the Shop!\n";
    cout << "===========================================\n";
    cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Type" << setw(10) << "Price\n";
    cout << "-------------------------------------------\n";

    for (int i = 0; i < items.getSize(); i++) {
        Item* currentItem = items.getIterator()->data;

        string itemType = "Unknown";
        if (dynamic_cast<Armor*>(currentItem)) {
            itemType = "Armor";
        } else if (dynamic_cast<Weapon*>(currentItem)) {
            itemType = "Weapon";
        } else if (dynamic_cast<Food*>(currentItem)) {
            itemType = "Food";
        }

        cout << left << setw(5) << currentItem->getID() 
             << setw(20) << currentItem->getName() 
             << setw(10) << itemType 
             << setw(10) << currentItem->getPrice() << endl;

        items.iterateOnce();
    }

    items.resetIterator();
    cout << "===========================================\n";
}


void Shop::printOptions() {
    cout << "1. Purchase Item by Index\n";
    cout << "2. Purchase Item by Name\n";
    cout << "3. Check Balance\n";
    cout << "4. Check current equipment\n";
    cout << "0. Exit\n";
}

void Shop::releaseElements() {
    items.release();
}

void Shop::release() {
    sInstance->releaseElements();
    delete sInstance;
    sInstance = nullptr;
}